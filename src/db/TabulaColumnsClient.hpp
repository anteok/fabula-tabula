//
// Created by kuimov on 04.08.23.
//

#ifndef TABULA_TABULACOLUMNSCLIENT_HPP
#define TABULA_TABULACOLUMNSCLIENT_HPP

#include "oatpp/orm/DbClient.hpp"
#include "oatpp/orm/SchemaMigration.hpp"

#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class TabulaColumnsDbClient : public oatpp::orm::DbClient {
public:

    TabulaColumnsDbClient(const std::shared_ptr<oatpp::orm::Executor>& executor) : oatpp::orm::DbClient(executor) {}

    TabulaColumnsDbClient(const std::shared_ptr<oatpp::orm::Executor>& executor, const bool migrate) : oatpp::orm::DbClient(executor) {
        if (migrate) {
            oatpp::orm::SchemaMigration migration(executor);
            migration.addFile(1, DATABASE_MIGRATIONS "/t_columns/001_init.sql");

            // New migrations should be added here

            migration.migrate();
        }
    }


    QUERY(getColumns,
        "SELECT * FROM TabulaColumns;")
};

#include OATPP_CODEGEN_END(DbClient)

#endif //TABULA_TABULACOLUMNSCLIENT_HPP
