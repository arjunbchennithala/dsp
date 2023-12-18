#include "DistrhoPlugin.hpp"

START_NAMESPACE_DISTRHO;

class Pixtortion : public Plugin {
public:
	Pixtortion()
		:Plugin(1, 0, 0),
		amount(1.0)
	{
		sample_rate = getSampleRate();
		
	}

protected:
	const char* getLabel() const override {
		return "Pixtortion";
	}

	const char* getMaker() const override {
		return "PixellQ";
	}

	const char*  getLicense() const override {
		return "----";
	}

	uint32_t getVersion() const override {
		return d_version(1, 0, 0);
	}

	int64_t getUniqueId() const override {
		return d_cconst('P', 'i', 'x', 'T');
	}

	void initParameter(uint32_t index, Parameter& parameter) override {
		parameter.hints = kParameterIsAutomatable;
		parameter.name = "Amount";
		parameter.symbol = "amount";
		parameter.unit = "%";
		parameter.ranges.min = 1.0f;
		parameter.ranges.max = 100.0f;
		parameter.ranges.def = 1.0f;
	}


	float getParameterValue(uint32_t index) const override {
		return amount;
	}

	void setParameterValue(uint32_t index, float value) override {
		amount = value/10;
	}

	void run(const float **inputs, float **outputs, uint32_t frames) override {
		const float* const input = inputs[0];
		float* const output = outputs[0];
		for(uint32_t i=0; i<frames; i++) {
			if(input[i] >= 0) {
				if(input[i]>(1/amount)) {
					output[i] = 1/amount;
				}else{
					output[i] = input[i];
				}
			}else {
				if(input[i]<(-1 * (1/amount))) {
					output[i] = -1 * (1/amount);
				}else{
					output[i] = input[i];
				}
			}

		}
	}

private:
	double sample_rate;
	float amount;
};

Plugin* createPlugin() {
	return new Pixtortion();
}

END_NAMESPACE_DISTRHO;
