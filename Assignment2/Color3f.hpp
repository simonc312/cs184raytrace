#ifndef COLOR3f_HPP
#define COLOR3f_HPP

class Color3f{
public:
	Color3f(float r = 0.0f, float g = 0.0f, float b = 0.0f);

	Color3f operator+(const Color3f& right) const;
	Color3f operator*(const Color3f& right) const;
	Color3f operator*(float right) const;

	float Red() const;
	float Green() const;
	float Blue() const;

	void Print() const;
private:
	float red, green, blue;
};

#endif//COLOR3f_HPP
