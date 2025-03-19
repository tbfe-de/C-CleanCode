#ifndef BASE_COUNTER_H
#define BASE_COUNTER_H

class BaseCounter {
protected:
	const int range_;
private:
	int value_;
	virtual void underflow();
	virtual long chained() const;
public:
	BaseCounter(int range, int value);
	void operator=(int);
	void Step1();
	void StepN(int distance);
	int GetValue() const;
	long Remaining() const;
};

#endif // include guard
