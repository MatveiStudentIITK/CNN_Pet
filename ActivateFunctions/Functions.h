#pragma once
#include"D:/My/Pets/Matrix/Matrix.h"
namespace My
{
	struct Function abstract
	{
		virtual const long double CalculateFunction(const long double& Arg) const = 0;
		const Matrix CalculateFunction(const Matrix& Arg) const;
		const Matrix* CalculateFunction(const Matrix* const& Arg, const size_t& Argc) const;
		virtual const long double CalculateDerivative(const long double& Arg) const = 0;
		const Matrix CalculateDerivative(const Matrix& Arg) const;
		const Matrix* CalculateDerivative(const Matrix* const& Arg, const size_t& Argc) const;
		enum class Type
		{
			Gaus,
			Sigm,
			SoftSign,
			Th,
			None
		};
		virtual const Type GetFunctionType() const = 0;
	};
	struct Gaus : Function
	{
		virtual const long double CalculateFunction(const long double& Arg) const override { return exp(-pow(Arg, 2)); }
		virtual const long double CalculateDerivative(const long double& Arg) const override { return -2 * Arg * exp(-pow(Arg, 2)); }
		const Type GetFunctionType() const { return Type::Gaus; }
	};
	struct Sigm : Function
	{
		virtual const long double CalculateFunction(const long double& Arg) const override { return 1 / (1 + exp(-Arg)); }
		virtual const long double CalculateDerivative(const long double& Arg) const override { return CalculateFunction(Arg) * (1 - CalculateFunction(Arg)); }
		const Type GetFunctionType() const { return Type::Sigm; }
	};
	struct SoftSign : Function
	{
		virtual const long double CalculateFunction(const long double& Arg) const override { return 1 / (1 - abs(Arg)); }
		virtual const long double CalculateDerivative(const long double& Arg) const override { return 1 / pow(1 - abs(Arg), 2); }
		const Type GetFunctionType() const { return Type::SoftSign; }
	};
	struct Th : Function
	{
		virtual const long double CalculateFunction(const long double& Arg) const override { return tanh(Arg); }
		virtual const long double CalculateDerivative(const long double& Arg) const override { return 1 - pow(CalculateFunction(Arg), 2); }
		const Type GetFunctionType() const { return Type::Th; }
	};
	struct None : Function
	{
		virtual const long double CalculateFunction(const long double& Arg) const override { return Arg; }
		virtual const long double CalculateDerivative(const long double& Arg) const override { return 1; }
		const Type GetFunctionType() const { return Type::None; }
	};
}