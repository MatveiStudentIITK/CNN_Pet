#include "Layers.h"

using namespace My;

void My::Dense::BackPropagate()
{
    PreOutputError  = Activation.CalculateDerivative(PreOutput);
    BiasError       = MultiplyByElements(PreOutputError, OutputError);
    WeightsErrors   = BiasError * Input.Transpose();
    if (Layer::InputError) InputError = Weights * PreOutputError * OutputError;
}
void My::Dense::Update()
{
    Weights += LearningRate * WeightsErrors;
    Bias    += LearningRate * BiasError;
}

const Matrix My::Convolution::Convolute(const Matrix& Input, const Matrix& Filter, const std::pair<size_t, size_t>& StepSize)
{
    Matrix Result(
        (Input.Height - Filter.Height) / StepSize.first + 1,
        (Input.Height - Filter.Width) / StepSize.second + 1);
    for (size_t i = 0; i < Input.Height; i += StepSize.first)
    {
        for (size_t j = 0; j < Input.Width; j += StepSize.second)
        {
            long double Sum = 0;
            for (size_t fi = 0; fi < Filter.Height; i++)
            {
                for (size_t fj = 0; fj < Filter.Width; fj++)
                {
                    Sum += Input.Elements[(i + fi) * Input.Width + (j + fj)] * Filter.Elements[fi * Filter.Width + fj];
                }
            }
            Result.Elements[(i / StepSize.first) * Result.Width + (j / StepSize.second)];
        }
    }
    return Result;
}
void My::Convolution::ForwardPropagate()
{
    for (size_t i = 0; i < InputCount; i++)
    {
        for (size_t i = 0; i < PaddedInput[i].Height; i++)
        {
            for (size_t j = 0; j < PaddedInput[i].Width; j++)
            {
                PaddedInput[i].Elements[i * PaddedInput[i].Width + j] = (
                    i >= PaddingSize.first && i < (Input[i].Height + PaddingSize.first - 1)
                    && j >= PaddingSize.second && j < (Input[i].Width + PaddingSize.second - 1) ?
                    Input[i].Elements[(i - PaddingSize.first) * Input[i].Width + (j - PaddingSize.second)] : 0);
            }
        }
        for (size_t f = 0; f < FiltersCount; f++)
        {
            Output[i * FiltersCount + f] = Activation.CalculateFunction(PreOutput[i * FiltersCount + f] = Convolute(PaddedInput[i], Filters[f], StepSize));
        }
    }
}
void My::Convolution::BackPropagate()
{
    for (size_t i = 0; i < OutputCount; i++) { PreOutputError[i] = Activation.CalculateDerivative(PreOutput[i]); }
    for (size_t i = 0; i < InputCount; i++)
    {
        for (size_t f = 0; f < FiltersCount; f++)
        {
            Filters[f] += Convolute(PaddedInput[i], PreOutputError[i * FiltersCount + f], { 1,1 });
        }
    }
}

#include"D:/My/Pets/ActivateFunctions/Functions.cpp"

void main()
{
}