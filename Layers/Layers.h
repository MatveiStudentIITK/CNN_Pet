#pragma once
#include"D:/My/Pets/ActivateFunctions/Functions.h"
namespace My
{
	struct Layer abstract
	{
		const long double LearningRate;
		const Function * const Activation;
		Layer
			* const PreviousLayer,
			* const FollowingLayer;
		Matrix
			* const & Input,
			* const Output,
			* const & InputError,
			* const OutputError;
		Layer(
			const long double& LearningRate,
			const Function* const& Activation,
			Layer * const & PreviousLayer,
			Layer * const & FollowingLayer,
			Matrix * const Input,
			Matrix * const Output,
			Matrix * const InputError,
			Matrix * const OutputError) :
			LearningRate(LearningRate),
			Activation(Activation),
			PreviousLayer(PreviousLayer),
			FollowingLayer(FollowingLayer),
			Input(Input),
			Output(Output),
			InputError(InputError),
			OutputError(OutputError) {}
		~Layer() {
			if (Activation) delete Activation;
		}
		virtual void ForwardPropagate() = 0;
		virtual void BackPropagate() = 0;
		virtual void Update() = 0;
		enum class Type
		{
			Dense,
			Convolution,
			Pool,
			FullConnect
		};
		virtual const Type GetType() = 0;
	};
	struct Dense : Layer
	{
		Layer
			& PreviousLayer		= * Layer::PreviousLayer,
			& FollowingLayer	= * Layer::FollowingLayer;
		const long double
			& LearningRate		= Layer::LearningRate;
		const Function
			& Activation		= * Layer::Activation;
		const Matrix
			& Input				= * Layer::Input;
		Matrix
			& Output			= * Layer::Output,
			& InputError		= * Layer::InputError,
			& OutputError		= * Layer::OutputError,
			PreOutput,
			Weights,
			Bias,
			PreOutputError,
			WeightsErrors,
			BiasError;
		Dense(
			const size_t & InputSize,
			const size_t & OutputSize,
			const long double & LearningRate,
			const Function * const & Activation,
			Layer * const & PreviousLayer,
			Layer * const & FollowingLayer) :
			PreOutput(OutputSize, 1),
			Weights(OutputSize, InputSize),
			Bias(OutputSize, 1),
			PreOutputError(OutputSize, 1),
			WeightsErrors(OutputSize, InputSize),
			BiasError(OutputSize, 1),
			Layer(
				LearningRate,
				Activation,
				PreviousLayer,
				FollowingLayer,
				new Matrix(InputSize, 1),
				new Matrix(OutputSize, 1),
				(PreviousLayer ? PreviousLayer->OutputError : nullptr),
				new Matrix(OutputSize, 1)) {}
		~Dense()
		{
			if (Layer::Input) delete Layer::Input, const_cast<Matrix*&>(Layer::Input) = nullptr;
			if (Layer::Output) delete Layer::Output;
			if (Layer::InputError) delete Layer::InputError, const_cast<Matrix*&>(Layer::InputError) = nullptr;
			if (Layer::OutputError) delete Layer::OutputError;
		}
		void ForwardPropagate() override { Output = Activation.CalculateFunction(PreOutput = Weights * Input + Bias); }
		void BackPropagate() override;
		void Update() override;
		const Type GetType() override { return Type::Dense; }
	};
	struct Convolution : Layer
	{
		const std::pair<size_t, size_t>
			StepSize,
			PaddingSize;
		const size_t
			InputCount,
			OutputCount,
			FiltersCount;
		Layer
			& PreviousLayer		= * Layer::PreviousLayer,
			& FollowingLayer	= * Layer::FollowingLayer;
		const long double
			& LearningRate		= Layer::LearningRate;
		const Function
			& Activation		= * Layer::Activation;
		const Matrix
			* const & Input		= Layer::Input,
			* const & PaddedInput;
		Matrix
			* Output			= Layer::Output,
			* InputError		= Layer::InputError,
			* OutputError		= Layer::OutputError,
			* const PreOutput,
			* const Filters,
			* const Bias,
			* const PreOutputError,
			* const FiltersErrors;
		Convolution(
			const long double & LearningRate,
			const std::pair<size_t, size_t>	& StepSize,
			const std::pair<size_t, size_t>	& PaddingSize,
			const size_t InputCount,
			const std::pair<size_t, size_t>	& InputSize,
			const size_t FiltersCount,
			const std::pair<size_t, size_t>	& FiltersSize,
			const Function* const& Activation,
			Layer* const& PreviousLayer,
			Layer* const& FollowingLayer) :
			StepSize(StepSize),
			PaddingSize(PaddingSize),
			InputCount(InputCount),
			FiltersCount(FiltersCount),
			OutputCount(InputCount * FiltersCount),
			PreOutput(new Matrix[OutputCount]),
			Filters(new Matrix[FiltersCount]),
			Bias(new Matrix[FiltersCount]),
			PaddedInput(new Matrix[InputCount]),
			PreOutputError(new Matrix[OutputCount]),
			FiltersErrors(new Matrix[FiltersCount]),
			Layer(
				LearningRate,
				Activation,
				PreviousLayer,
				FollowingLayer,
				new Matrix[InputCount],
				new Matrix[OutputCount],
				(PreviousLayer ? PreviousLayer->OutputError : nullptr),
				new Matrix[OutputCount]) {}
		~Convolution()
		{
			if (Input) delete[InputCount * sizeof(Matrix)] Input, const_cast<Matrix*&>(Input) = nullptr;
			if (Output) delete[FiltersCount * sizeof(Matrix)] Output;
			if (InputError) delete[InputCount * sizeof(Matrix)] InputError, const_cast<Matrix*&>(InputError) = nullptr;
			if (OutputError) delete[OutputCount * sizeof(Matrix)] Output;
		}
		const Matrix Convolute(const Matrix& Input, const Matrix& Filter, const std::pair<size_t, size_t>& StepSize);
		void ForwardPropagate() override;
		void BackPropagate() override;
		void Update() override;
		const Type GetType() override { return Type::Convolution; }
	};
	struct Pool : Layer
	{
	};
	struct FullConnect : Layer
	{
	};
}