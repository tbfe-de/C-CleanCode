#ifndef CHAIN_COUNTER_H
#define CHAIN_COUNTER_H

#include "BaseCounter.h"

class ChainCounter : public BaseCounter {
private:
	class BaseCounter& next_;
	void underflow() override;
	long chained() const override;
public:
	ChainCounter(int range, int value, BaseCounter&);
	using BaseCounter::operator=;
};

#endif // include guard
