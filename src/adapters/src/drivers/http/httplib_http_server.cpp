#include "httplib_http_server.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include "../logger/spdlog_logger.hpp"

HttplibHTTPServer::HttplibHTTPServer()
{
    m_service = std::unique_ptr<httplib::Server>(new httplib::Server());
}

HttplibHTTPServer::~HttplibHTTPServer()
{
    stop();
}

void HttplibHTTPServer::route(
    const std::string & _path,
    const std::string & _method,
    const std::function <void (
        const httplib::Request &,
        httplib::Response &)
    > & _handler)
{
        std::string method(_method.size(), 0);
        std::transform(_method.begin(), _method.end(), method.begin(), ::toupper);

        {
            std::stringstream msg;
            msg << "Defining route for path " << _path << " method " << method;
            SpdlogLogger::info(__FILE__, msg.str());
        }

        if(method == "GET")
        {
            m_service->Get(_path, _handler);
        }
        else if(method == "POST")
        {
            m_service->Post(_path, _handler);
        }
        else if(method == "PUT")
        {
            m_service->Put(_path, _handler);
        }
        else if(method == "DELETE")
        {
            m_service->Delete(_path, _handler);
        }
        else if(method == "PATCH")
        {
            m_service->Patch(_path, _handler);
        }
        else
        {
            std::stringstream msg;
            msg << "Invalid HTTP method:" << _method << std::endl;
            throw std::runtime_error(msg.str());
        }
}

void HttplibHTTPServer::start(
    const std::string & _ip,
    unsigned int _port,
    unsigned int _threads)
{
    stop();

    if(!m_thread_service)
    {
        m_thread_service = std::unique_ptr<std::thread>(
                               new std::thread(
                                   [this, _ip, _port, _threads]()
        {
            if(_threads > 0)
            {
                m_service->new_task_queue = [_threads] {
                    return new httplib::ThreadPool(_threads);
                };
            }
            std::stringstream msg;
            msg << "Server starting at " <<_ip << ":" << _port;
            SpdlogLogger::info(__FILE__, msg.str());

            m_service->listen(_ip, _port);
        }));
    }
}

void HttplibHTTPServer::wait()
{
    if(m_thread_service)
    {
        m_thread_service->join();
    }

    m_thread_service.reset();
}

void HttplibHTTPServer::stop()
{
    if(m_service->is_running())
    {
        m_service->stop();
    }

    wait();
}
