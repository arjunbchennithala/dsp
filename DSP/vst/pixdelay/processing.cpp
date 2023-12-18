#include "DistrhoPlugin.hpp"

START_NAMESPACE_DISTRHO;

class PixDelay : public Plugin {
public:
	PixDelay()
		:Plugin(4, 0, 0), 
		time(0.0f), 
		dry(0.5f),
		wet(0.5),
		feedback(0.0f),
		line_length(96000),
		read_index(0)
	{
		sample_rate = getSampleRate();
		write_index = (sample_rate/1000) * 100; 
		for(int i=0; i<=line_length; i++) {
			delay_line[i] = 0.0;
		}
	}

protected:
	const char* getLabel() const override {
		return "PixDelay";
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
		return d_cconst('P', 'i', 'x', 'D');
	}

	void initParameter(uint32_t index, Parameter& parameter) override {
		parameter.hints = kParameterIsAutomatable;

		switch(index) {
			case 0:
				parameter.name = "Delay time";
				parameter.symbol = "time";
				parameter.unit = "ms";
				parameter.ranges.min = 10.0f;
				parameter.ranges.max = 2000.0f;
				parameter.ranges.def = 100.0f;
				break;
			case 1:
				parameter.name = "Feedback Level";
				parameter.symbol = "feedback";
				parameter.ranges.min = 0.0f;
				parameter.ranges.max = 1.0f;
				parameter.ranges.def = 0.5f;
				break;
			case 2:
				parameter.name = "Dry";
				parameter.unit = "%";
				parameter.symbol = "dry";
				parameter.ranges.min = 1.0f;
		                parameter.ranges.max = 100.0f;
                		parameter.ranges.def = 50.0f;
				break;
			case 3:
				parameter.name = "Wet";
				parameter.unit = "%";
				parameter.symbol = "wet";
				parameter.ranges.min = 1.0f;
				parameter.ranges.max = 100.0f;
				parameter.ranges.def = 50.0f;
		}
	}


	float getParameterValue(uint32_t index) const override {
		switch(index) {
			case 0:
				return time;
				break;
			case 1:
				return feedback;
				break;
			case 2:
				return dry;
				break;
			case 3:
				return wet;
				break;
		}
		return 0;
	}

	void setParameterValue(uint32_t index, float value) override {
		switch(index) {
			case 0:
				time = value;
				write_index = (int)(sample_rate/1000)*time;
				write_index = (read_index+write_index)%line_length;
				for(int i=0; i<line_length; i++) {
					delay_line[i] = 0.0;
				}
				break;
			case 1:
				feedback = value;
				break;
			case 2:
				dry = value/100;
				break;
			case 3:
				wet = value/100;
				break;
		}
	}

	void run(const float **inputs, float **outputs, uint32_t frames) override {
		const float* const input = inputs[0];
		float* const output = outputs[0];
		for(uint32_t i=0; i<frames; i++) {
			delay_line[write_index] = input[i] + delay_line[read_index] * feedback;
			output[i] = delay_line[read_index]*wet + input[i]*dry;
			read_index = (read_index+1)%line_length;
			write_index = (write_index+1)%line_length;

		}
	}

private:
	float time;
	float dry;
	float wet;
	float feedback;
	float delay_line[96001];
	int line_length;
	double sample_rate;
	int read_index;
	int write_index;
};

Plugin* createPlugin() {
	return new PixDelay();
}

END_NAMESPACE_DISTRHO;
