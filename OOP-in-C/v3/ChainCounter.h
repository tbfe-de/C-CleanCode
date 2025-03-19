#ifndef CHAIN_COUNTER_H
#define CHAIN_COUNTER_H

class ChainCounter {
private:
	const int range_;
	int value_;
	class ChainCounter* const next_;
public:
	ChainCounter(int range, int value, ChainCounter* const next = nullptr);
	void operator=(int);
	bool Step1();
	void StepN(int distance);
	int GetValue() const;
	long Remaining() const;
};

#endif // include guard
