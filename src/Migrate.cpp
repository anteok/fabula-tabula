//
// Created by kuimov on 13.08.23.
//
#include "oatpp/core/macro/component.hpp"
#include "oatpp-postgresql/orm.hpp"

#include "db/TabulaColumnsClient.hpp"

int main() {
    auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(
            "postgresql://admin:pass@127.0.0.1:5432/tabula");
    auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                                          10,
                                                                          std::chrono::seconds(5));
    auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);
    std::shared_ptr<TabulaColumnsDbClient> dbClient = std::make_shared<TabulaColumnsDbClient>(executor, true);
}
