#include <Solution.h>
#include <cstdint>
#include <algorithm>
#include <cstring>

#include "utils/Image.h"
#include "utils/FunctionTracer.h"
#include "utils/EyePatterns.h"

static bool isTooRed(uint8_t red)
{
    return red >= 200;
}

static uint8_t redFilter(uint8_t redPixel)
{
    return redPixel - 150;
}

static std::pair<bool, std::vector<size_t>> matchPattern(const size_t beginIndex, const StrideImage & image, const EyePattern & pattern)
{
    bool itsAMatch = true;
    std::vector<size_t> indices;

    for (size_t i = 0; i < EYE_PATTERN_COL_SIZE && itsAMatch; ++i)
    {
        size_t index = beginIndex + image.resolution.width * i;
        const char * line = pattern[i];
        const size_t len = strlen(line);
        for (size_t j = 0; j < len && itsAMatch; ++j, ++index)
        {
            if (line[j] == ' ')
            {
                itsAMatch = !isTooRed(image.redPixels[index]);
            }
            else
            {
                itsAMatch = isTooRed(image.redPixels[index]);
                indices.push_back(index);
            }
        }
    }
    return {itsAMatch, indices};
}

static std::vector<size_t> findTooRedPixels(const StrideImage & image)
{
    std::vector<size_t> tooRed;
    for (const auto & eyePattern : EYE_PATTERNS)
    {
        for (size_t i = 0; i < image.redPixels.size(); ++i)
        {
            if (isTooRed(image.redPixels[i]) && std::none_of(tooRed.begin(), tooRed.end(), [i](size_t x){ return x == i; })) // there's a chance this is an eye
            {
                auto [itsAMatch, redIndices] = matchPattern(i, image, eyePattern);
                if(itsAMatch)
                {
                    tooRed.insert(tooRed.end(), redIndices.begin(), redIndices.end());
                }
            }
        }
    }
    return tooRed;
}

static void applyFilter(const std::vector<size_t> & eye, StrideImage & image)
{
    for(auto index : eye)
    {
        image.redPixels[index] = redFilter(image.redPixels[index]);
    }
}

void Solution::compute(std::vector <StrideImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

    for (auto & image : images)
    {
        const std::vector<size_t> tooRedPixels = findTooRedPixels(image);
        applyFilter(tooRedPixels, image);
    }
}
