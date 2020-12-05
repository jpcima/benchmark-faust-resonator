
struct Meta {
    void declare(const char *name, const char *value) {}
};

struct UI {
    void openVerticalBox(const char *name) {}
    void closeBox() {}
    void addHorizontalSlider(const char *name, float *control, float def, float min, float max, float step) {}
    void declare(float *control, const char *name, const char *value) {}
};

class one_sample_dsp {
public:
    virtual ~one_sample_dsp() {}
};

<<includeIntrinsic>>
<<includeclass>>

#include <benchmark/benchmark.h>
#include <vector>

class StringResonator : public benchmark::Fixture {
public:
    StringResonator()
    {
        resonator.init(44100);
        icontrol.resize(resonator.getNumIntControls());
        fcontrol.resize(resonator.getNumRealControls());
    }
    void SetUp(const ::benchmark::State& state)
    {
        resonator.instanceClear();
        resonator.control(icontrol.data(), fcontrol.data());
    }
    void TearDown(const ::benchmark::State&)
    {
    }
    Resonator resonator;
    std::vector<int> icontrol;
    std::vector<float> fcontrol;
};

BENCHMARK_DEFINE_F(StringResonator, StringResonator)(benchmark::State& state)
{
    size_t numFrames = state.range(0);

    for (auto _ : state)
    {
        float input = 0.5f;
        float output;
        for (size_t i = 0; i < numFrames; ++i)
            resonator.compute(&input, &output, icontrol.data(), fcontrol.data());
    }
}

BENCHMARK_REGISTER_F(StringResonator, StringResonator)->RangeMultiplier(2)->Range(16, 1024);
BENCHMARK_MAIN();
