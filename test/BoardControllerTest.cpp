//
// Created by kuimov on 04.08.23.
//

#include "BoardControllerTest.hpp"

#include "controller/BoardController.hpp"

#include "app/TabulaApiTestClient.hpp"
#include "app/TestComponent.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"

#include "oatpp-test/web/ClientServerTestRunner.hpp"

void BoardControllerTest::onRun() {

    TestComponent component;

    oatpp::test::web::ClientServerTestRunner runner;
    runner.addController(std::make_shared<BoardController>());

    runner.run([this, &runner] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);
        auto client = TabulaApiTestClient::createShared(requestExecutor, objectMapper);

        auto response = client->getBoardColumns();
        OATPP_ASSERT(response->getStatusCode() == 200);

        auto message = response->readBodyToDto<oatpp::Object<BoardColumnDTO>>(objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->statusCode == 200);
        OATPP_ASSERT(message->message == "The board will be there soon");

    }, std::chrono::minutes(10));

    std::this_thread::sleep_for(std::chrono::seconds(1));
}