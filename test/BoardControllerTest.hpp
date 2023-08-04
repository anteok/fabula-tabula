//
// Created by kuimov on 04.08.23.
//

#ifndef TABULA_BOARDCONTROLLERTEST_HPP
#define TABULA_BOARDCONTROLLERTEST_HPP

#include "oatpp-test/UnitTest.hpp"

class BoardControllerTest : public oatpp::test::UnitTest {
public:
    BoardControllerTest() : UnitTest("TEST[BoardControllerTest]") {}
    void onRun() override;
};

#endif //TABULA_BOARDCONTROLLERTEST_HPP
