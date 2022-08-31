#include <Solution.h>
#include <cstdint>
#include <algorithm>
#include <cstring>

#include "utils/Image.h"
#include "utils/FunctionTracer.h"
#include "utils/EyePatterns.h"

static bool isRedEnough(uint8_t red)
{
    return red >= 200;
}

static uint8_t redFilter(uint8_t redPixel)
{
    return redPixel - 150;
}

static bool matchInner(const size_t beginIndex, const StrideImage & image, const EyePattern & pattern)
{
    bool itsAMatch = true;
    for (size_t i = 0; i < pattern.size() && itsAMatch; ++i)
    {
        size_t index = beginIndex + image.resolution.width * i;
        const char * line = pattern[i];
        const size_t len = strlen(line);
        for (int j = 0; j < len && itsAMatch; ++j, ++index)
        {
            if (line[j] == ' ')
            {
                itsAMatch = !isRedEnough(image.redPixels[index]);
            }
            else
            {
                itsAMatch = isRedEnough(image.redPixels[index]); // TODO: Only red pixels are taken into account?
            }
        }
    }
    return itsAMatch;
}

static std::vector<EyeLocation> match(const StrideImage & image)
{
    std::vector<EyeLocation> matches;
    for (uint32_t eyePatternIndex = 0; eyePatternIndex < EYE_PATTERNS_COUNT; ++eyePatternIndex)
    {
        for (size_t i = 0; i < image.redPixels.size(); ++i)
        {
            const uint8_t redPixel = image.redPixels[i];
            if (isRedEnough(redPixel) && matchInner(i, image, EYE_PATTERNS[eyePatternIndex]))
            {
                matches.push_back((EyeLocation){ .location = i, .type = eyePatternIndex });
            }
        }
    }
    return std::move(matches);
}

static void applyFilter(const EyeLocation & eye, StrideImage & image)
{
    EyePattern pattern = EYE_PATTERNS[eye.type];
    size_t beginIndex = eye.location;

    for (size_t i = 0; i < pattern.size(); ++i)
    {
        const char * line = pattern[i];
        const size_t len = strlen(line);
        size_t index = beginIndex + image.resolution.width * i;
        for (size_t j = 0; j < len; ++j, ++index)
        {
            if (line[j] != ' ')
            {
                image.redPixels[index] = redFilter(image.redPixels[index]);
            }
        }
    }
}

void Solution::compute(std::vector <StrideImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

    for (auto & image : images)
    {
        std::vector<EyeLocation> eyes = match(image);
        for (auto & eye : eyes)
        {
            applyFilter(eye, image);
        }
    }
}
