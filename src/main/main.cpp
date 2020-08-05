#include <adapters/adapters_factory.hpp>
#include <application/application_factory.hpp>

int main()
{
    auto config_ldr = AdaptersFactory::makeConfigLoader("yaml");
    auto config = config_ldr->load("resources/config.yaml");

    auto logger = AdaptersFactory::makeLogger();
    logger->setLoggerPath(config.logger.path);

    auto persistence = AdaptersFactory::makePersistence(
        config.persistence.driver);
    persistence->init(config.persistence.parameters);

    auto author_rp = AdaptersFactory::makeAuthorsRepository(*persistence);

    auto add_author_uc = ApplicationFactory::makeAddAuthorUsecase(*author_rp);

    auto http_srv = AdaptersFactory::makeHTTPServer();
    auto health_cnt = AdaptersFactory::makeHTTPHealthCheckController(*http_srv);
    auto author_cnt = AdaptersFactory::makeHTTPAuthorsController(
        *add_author_uc, *http_srv);

    http_srv->start(config.http.host, config.http.port, config.http.threads);
    http_srv->wait();

    return 0;
}
