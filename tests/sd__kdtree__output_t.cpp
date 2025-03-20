#include "pch.hpp"
#include <search/output.hpp>

int 
main(void) 
{

        using namespace sd::kdtree;

       #define TEST_OUTPUT_T(TYPE_I, TYPE_F, TEST_NAME)                       \
            TEST_NAME "_default constructor"_test = [] {                      \
                    output_t<TYPE_I, TYPE_F> out;                             \
                    expect(out.idx() == (TYPE_I)0);                           \
                    expect(out.dst() == std::numeric_limits<TYPE_F>::max());  \
            };                                                                \
            TEST_NAME "_parameter constructor"_test = [] {                    \
                    output_t<TYPE_I, TYPE_F> out((TYPE_I)42, (TYPE_F)3.14);   \
                    expect(out.idx() == (TYPE_I)42);                          \
                    expect(out.dst() == (TYPE_F)3.14);                        \
            };                                                                \
            TEST_NAME "_getters and setters"_test = [] {                      \
                    output_t<TYPE_I, TYPE_F> out;                             \
                    out.idx((TYPE_I)10);                                      \
                    out.dst((TYPE_F)2.5);                                     \
                    expect(out.idx() == (TYPE_I)10);                          \
                    expect(out.dst() == (TYPE_F)2.5);                         \
            };                                                                \
            TEST_NAME "_arithmetic ops"_test = [] {                           \
                    output_t<TYPE_I, TYPE_F> o1((TYPE_I)1, (TYPE_F)2.0);      \
                    output_t<TYPE_I, TYPE_F> o2((TYPE_I)3, (TYPE_F)4.5);      \
                    auto sum = o1 + o2;                                       \
                    expect(sum.idx() == (TYPE_I)(1 + 3));                     \
                    expect(sum.dst() == (TYPE_F)(2.0 + 4.5));                 \
                    auto diff = o2 - o1;                                      \
                    expect(diff.idx() == (TYPE_I)(3 - 1));                    \
                    expect(diff.dst() == (TYPE_F)(4.5 - 2.0));                \
                    o1 += o2;                                                 \
                    expect(o1.idx() == (TYPE_I)4);                            \
                    expect(o1.dst() == (TYPE_F)6.5);                          \
                    o2 -= output_t<TYPE_I, TYPE_F>((TYPE_I)1, (TYPE_F)1.5);   \
                    expect(o2.idx() == (TYPE_I)2);                            \
                    expect(o2.dst() == (TYPE_F)3.0);                          \
            };                                                                \
            TEST_NAME "_operator*(S, output_t)"_test = [] {                   \
                    output_t<TYPE_I, TYPE_F> out((TYPE_I)2, (TYPE_F)3.0);     \
                    {                                                         \
                            auto mul = 2 * out;                               \
                            expect(mul.idx() == (TYPE_I)(2 * 2));             \
                            expect(mul.dst() == (TYPE_F)(2 * 3.0));           \
                    }                                                         \
                    {                                                         \
                            auto mulf = 2.5 * out;                            \
                            expect(mulf.idx() == (TYPE_I)(2.5 * 2));          \
                            expect(mulf.dst() == (TYPE_F)(2.5 * 3.0));        \
                    }                                                         \
            }

        TEST_OUTPUT_T(std::uint32_t, float,  "[output_t<uint32_t, float>]");
        TEST_OUTPUT_T(std::uint64_t, float,  "[output_t<uint64_t, float>]");
        TEST_OUTPUT_T(std::uint32_t, double, "[output_t<uint32_t, double>]");
        TEST_OUTPUT_T(std::uint64_t, double, "[output_t<uint64_t, double>]");
 
        "[is_output_t - true]"_test = [] {
                expect((is_output_t<output_t<int, float>>::value));
        };
 
        "[is_output_t - false]"_test = [] {
                expect((!is_output_t<int>::value));
        };
 
        "[output concept - satisfied]"_test = [] {
                static_assert(output<output_t<int, double>>);
        };

        "[output_t default constructor]"_test = [] {
                output_t<int, double> out; 
                expect(out.idx() == 0_i); 
                expect(out.dst() == std::numeric_limits<double>::max());
        };

        "[output_t parameter constructor]"_test = [] {
                output_t<int, double> out(42, 3.14);
                expect(out.idx() == 42_i);
                expect(out.dst() == 3.14_d);
        };

        "[output_t idx/dst getters and setters]"_test = [] {
                output_t<int, float> out;
                out.idx(10);
                out.dst(2.5f);
                expect(out.idx() == 10_i);
                expect(out.dst() == 2.5_f);
        };

        "[output_t operator->]"_test = [] {
                output_t<int, float> out(1, 1.0f);
                expect(out->idx() == 1_i);
                expect(out->dst() == 1.0_f);
        };

        "[output_t begin()]"_test = [] {
                output_t<int, float> out(2, 2.0f);
                auto b = out.begin();
                expect(b->idx() == 2_i);
                expect(b->dst() == 2.0_f);
        };

        "[output_t operator+]"_test = [] {
                output_t<int, double> o1(1, 3.0), o2(2, 4.0);
                auto o3 = o1 + o2;
                expect(o3.idx() == 3_i);
                expect(o3.dst() == 7.0_d);
        };

        "[output_t operator-]"_test = [] {
                output_t<int, double> o1(5, 7.0), o2(2, 4.0);
                auto o3 = o1 - o2;
                expect(o3.idx() == 3_i);
                expect(o3.dst() == 3.0_d);
        };

        "[output_t operator+=]"_test = [] {
                output_t<int, double> o1(1, 1.5), o2(2, 2.5);
                o1 += o2;
                expect(o1.idx() == 3_i);
                expect(o1.dst() == 4.0_d);
        };

        "[output_t operator-=]"_test = [] {
                output_t<int, double> o1(5, 5.5), o2(2, 2.0);
                o1 -= o2;
                expect(o1.idx() == 3_i);
                expect(o1.dst() == 3.5_d);
        };

        "[output_t operator*(S, output_t)]"_test = [] {
                output_t<int, double> o(3, 4.0);
                auto mul1 = 2 * o; 
                expect(mul1.idx() == 6_i);
                expect(mul1.dst() == 8.0_d);

                auto mul2 = 2.5 * o;
                expect(mul2.idx() == 7_i);
                expect(mul2.dst() == 10.0_d);
        };

        return 0;
}
