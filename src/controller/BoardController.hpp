//
// Created by kuimov on 04.08.23.
//

#ifndef TABULA_BOARDCONTROLLER_HPP
#define TABULA_BOARDCONTROLLER_HPP

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 * Board API Controller
 */
class BoardController : public oatpp::web::server::api::ApiController {
public:
    /**
     * Constructor with ObjectMapper.
     * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
     */
    BoardController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper)
    {}

    ENDPOINT("GET", "board", root) {
        auto dto = BoardDto::createShared();
        dto->statusCode = 200;
        dto->message = "The board will be there soon";
        return createDtoResponse(Status::CODE_200, dto);
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif //TABULA_BOARDCONTROLLER_HPP
