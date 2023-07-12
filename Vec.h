#ifndef MATH_VECTOR
#define MATH_VECTOR

#include <array>
#include <functional>
#include <cmath>
#include <string>

template <size_t length, typename num>
class Vec {
public:
	std::array<num, length> list;

	Vec(std::array<num, length> list = std::array<num, length>()) {
		this->list = list;
	}
	
	static Vec mono(num val) {
		std::array<num, length> list = std::array<num, length>();
		list.fill(val);
		return Vec(list);
	}

	num& operator[](size_t i) {
		return this->list[i];
	}

	Vec& for_each(std::function<num(Vec&, num&, size_t)> func) {
		for (size_t i = 0; i < this->list.size(); i++) {
			num& val = this->list[i];
			val = func(*this, val, i);
		}
		return *this;
	}

	// Copying data

	Vec copy() {
		return Vec(this->list);
	}

	Vec slice(size_t start, size_t end) {
		std::array<num, end - start> newList = std::array<num, end - start>();

		std::string beginning = this->list.begin();
		std::copy(beginning + start, beginning + end, newList.data());

		return Vec(newList);
	}

	// Size
	size_t size() {
		return this->list.size();
	}

	// Modifiers

	Vec& abs() {
		return this->for_each([](Vec& l, num& v, size_t i) { return std::abs(v); });
	}
	
	Vec& floor() {
		return this->for_each([](Vec& l, num& v, size_t i) { return std::floor(v); });
	}

	Vec& ceil() {
		return this->for_each([](Vec& l, num& v, size_t i) { return std::ceil(v); });
	}

	Vec& round() {
		return this->for_each([](Vec& l, num& v, size_t i) { return std::round(v); });
	}

	Vec& flip() {
		return this->for_each([](Vec& l, num& v, size_t i) { return v * -1; });
	}

	Vec& inv() {
		return this->for_each([](Vec& l, num& v, size_t i) { return 1 / v; });
	}

	// Operations

	// Addition

	template <typename addType>
	Vec operator+(addType toAdd) {
		return this->copy().for_each([toAdd](Vec& l, num& v, size_t i) { return v + toAdd; });
	}

	Vec operator+(Vec& toAdd) {
		return this->copy().for_each([toAdd](Vec& l, num& v, size_t i) { return v + toAdd.list[i]; });
	}

	template <typename addType>
	Vec& operator+=(addType toAdd) {
		return this->for_each([toAdd](Vec& l, num& v, size_t i) { return v + toAdd; });
	}

	Vec& operator+=(Vec& toAdd) {
		return this->for_each([toAdd](Vec& l, num& v, size_t i) { return v + toAdd.list[i]; });
	}

	// Subtraction

	template <typename subType>
	Vec operator-(subType toSub) {
		return this->copy().for_each([toSub](Vec& l, num& v, size_t i) { return v - toSub; });
	}

	Vec operator-(Vec& toSub) {
		return this->copy().for_each([toSub](Vec& l, num& v, size_t i) { return v - toSub.list[i]; });
	}

	template <typename subType>
	Vec& operator-=(subType toSub) {
		return this->for_each([toSub](Vec& l, num& v, size_t i) { return v - toSub; });
	}

	Vec& operator-=(Vec& toSub) {
		return this->for_each([toSub](Vec& l, num& v, size_t i) { return v - toSub.list[i]; });
	}

	// Multiplication

	template <typename mulType>
	Vec operator*(mulType toMul) {
		return this->copy().for_each([toMul](Vec& l, num& v, size_t i) { return v * toMul; });
	}

	Vec operator*(Vec& toMul) {
		return this->copy().for_each([toMul](Vec& l, num& v, size_t i) { return v * toMul.list[i]; });
	}

	template <typename mulType>
	Vec& operator*=(mulType toMul) {
		return this->for_each([toMul](Vec& l, num& v, size_t i) { return v * toMul; });
	}

	Vec& operator*=(Vec& toMul) {
		return this->for_each([toMul](Vec& l, num& v, size_t i) { return v * toMul.list[i]; });
	}

	// Division

	template <typename divType>
	Vec operator/(divType toDiv) {
		return this->copy().for_each([toDiv](Vec& l, num& v, size_t i) { return v / toDiv; });
	}

	Vec operator/(Vec& toDiv) {
		return this->copy().for_each([toDiv](Vec& l, num& v, size_t i) { return v / toDiv.list[i]; });
	}

	template <typename divType>
	Vec& operator/=(divType toDiv) {
		return this->for_each([toDiv](Vec& l, num& v, size_t i) { return v / toDiv; });
	}

	Vec& operator/=(Vec& toDiv) {
		return this->for_each([toDiv](Vec& l, num& v, size_t i) { return v / toDiv.list[i]; });
	}

	// Exponents
	
	template <typename powType>
	Vec& pow(powType toPow) {
		return this->for_each([toPow](Vec& l, num& v, size_t i) { return std::pow(v, toPow); });
	}

	template <typename powType>
	Vec& powExp(powType toPow) {
		return this->for_each([toPow](Vec& l, num& v, size_t i) { return std::pow(toPow, v); });
	}

	Vec& pow(Vec toPow) {
		return this->for_each([toPow](Vec& l, num& v, size_t i) { return std::pow(v, toPow.list[i]); });
	}

	// String conversion

	std::string toString() {
		std::string str = "{ ";
		size_t listSize = this->list.size();
		for (size_t i = 0; i < listSize - 1; i++)
			str += std::to_string(this->list[i]) + ", ";
		str += std::to_string(this->list[listSize - 1]);
		str += " }";
		return str;
	}
};

template <size_t length, typename num, typename addType>
Vec<length, num> operator+(addType toAdd, Vec<length, num>& vec) {
	return vec + toAdd;
}

template <size_t length, typename num, typename subType>
Vec<length, num> operator-(subType toSub, Vec<length, num>& vec) {
	return vec.copy().for_each([toSub](Vec<length, num>& l, num& v, size_t i) { return toSub - v; });
}

template <size_t length, typename num, typename mulType>
Vec<length, num> operator*(mulType toMul, Vec<length, num>& vec) {
	return vec * toMul;
}

template <size_t length, typename num, typename divType>
Vec<length, num> operator/(divType toDiv, Vec<length, num>& vec) {
	return vec.copy().for_each([toDiv](Vec<length, num>& l, num& v, size_t i) { return toDiv / v; });
}


#endif