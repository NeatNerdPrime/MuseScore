/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MUSE_MPE_MPETYPES_H
#define MUSE_MPE_MPETYPES_H

#include <stdint.h>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <vector>

#include "types/sharedhashmap.h"
#include "types/sharedmap.h"
#include "realfn.h"

#include "soundid.h"

#ifdef C
#undef C
#endif

namespace muse::mpe {
// common
using usecs_t = int64_t; // microseconds
using percentage_t = int_fast16_t;
constexpr percentage_t ONE_PERCENT = 100;
constexpr percentage_t FIFTY_PERCENT = ONE_PERCENT * 50;
constexpr percentage_t HUNDRED_PERCENT = ONE_PERCENT * 100;
constexpr percentage_t TEN_PERCENT = ONE_PERCENT * 10;

constexpr inline float percentageToFactor(const percentage_t percents)
{
    return static_cast<float>(percents) / static_cast<float>(HUNDRED_PERCENT);
}

constexpr inline percentage_t percentageFromFactor(const float factor)
{
    return static_cast<percentage_t>(factor * HUNDRED_PERCENT);
}

// Arrangement
using timestamp_t = usecs_t;
using duration_t = usecs_t;
using duration_percentage_t = percentage_t;
using voice_layer_idx_t = uint_fast8_t;
using staff_layer_idx_t = uint_fast16_t;
using layer_idx_t = size_t;

static constexpr duration_t INFINITE_DURATION = std::numeric_limits<duration_t>::max();

struct TimestampAndDuration {
    timestamp_t timestamp = 0;
    duration_t duration = 0;
};

static constexpr voice_layer_idx_t MAX_VOICES = 4;

constexpr inline layer_idx_t makeLayerIdx(const staff_layer_idx_t staffIdx, const voice_layer_idx_t voiceIdx)
{
    return staffIdx * MAX_VOICES + voiceIdx;
}

constexpr inline duration_percentage_t occupiedPercentage(const timestamp_t timestamp,
                                                          const duration_t overallDuration)
{
    return percentageFromFactor(static_cast<float>(timestamp) / static_cast<float>(overallDuration));
}

template<typename T>
struct ValuesCurve : public SharedMap<duration_percentage_t, T>
{
    std::pair<duration_percentage_t, T> amplitudeValuePoint() const
    {
        auto max = std::max_element(this->cbegin(), this->cend(), [](const auto& f, const auto& s) {
            return std::abs(f.second) < std::abs(s.second);
        });

        if (max == this->cend()) {
            static std::pair<duration_percentage_t, T> empty;
            return empty;
        }

        return *max;
    }

    T maxAmplitudeLevel() const
    {
        return amplitudeValuePoint().second;
    }

    duration_percentage_t attackPhaseDuration() const
    {
        return amplitudeValuePoint().first;
    }

    duration_percentage_t releasePhaseDuration() const
    {
        return this->empty() ? 0 : this->rbegin()->first - amplitudeValuePoint().first;
    }

    float velocityFraction() const
    {
        auto amplitudePoint = amplitudeValuePoint();
        duration_percentage_t duration = amplitudePoint.first;
        T amplitude = amplitudePoint.second;

        if (duration == 0) {
            return 1.f;
        }

        float factor = log10f(amplitude / static_cast<float>(duration));

        return (factor + 1.f) / 2.f;
    }
};

// Pitch
enum class PitchClass : signed char {
    Undefined = -1,
    C = 0,
    C_sharp = 1,
    D = 2,
    D_sharp= 3,
    E = 4,
    F = 5,
    F_sharp = 6,
    G = 7,
    G_sharp = 8,
    A = 9,
    A_sharp = 10,
    B = 11,

    Last
};

using octave_t = uint_fast8_t;
using pitch_level_t = percentage_t;
using PitchCurve = ValuesCurve<pitch_level_t>;

constexpr size_t EXPECTED_SIZE = (HUNDRED_PERCENT / TEN_PERCENT) + 1;

constexpr pitch_level_t PITCH_LEVEL_STEP = 50;
constexpr pitch_level_t MAX_PITCH_LEVEL = HUNDRED_PERCENT;
constexpr octave_t MAX_SUPPORTED_OCTAVE = 17; // 0 - 17

constexpr inline pitch_level_t pitchLevel(const PitchClass pitchClass, const octave_t octave)
{
    return (PITCH_LEVEL_STEP * (static_cast<int>(PitchClass::Last)) * octave) + (PITCH_LEVEL_STEP * static_cast<int>(pitchClass));
}

constexpr inline pitch_level_t pitchLevelDiff(const PitchClass fClass, const octave_t fOctave,
                                              const PitchClass sClass, const octave_t sOctave)
{
    return pitchLevel(fClass, fOctave) - pitchLevel(sClass, sOctave);
}

constexpr inline size_t pitchStepsCount(const pitch_level_t pitchRange)
{
    size_t range = pitchRange > 0 ? pitchRange : -pitchRange;
    return range / PITCH_LEVEL_STEP;
}

// Expression
using ArticulationFamily = mpe::SoundCategory;

enum class ArticulationType : signed char {
    Undefined = -1,

    // single note articulations
    Standard,
    Staccato,
    Staccatissimo,
    Tenuto,
    Marcato,
    Accent,
    SoftAccent,

    LaissezVibrer,
    LetRing,

    Subito,

    FadeIn,
    FadeOut,

    Harmonic,
    JazzTone,
    PalmMute,
    Mute,
    Open,
    Pizzicato,
    SnapPizzicato,
    RandomPizzicato,
    UpBow,
    DownBow,
    Detache,
    Martele,
    Jete,
    ColLegno,
    SulPont,
    SulTasto,

    GhostNote,
    CrossNote,
    CrossLargeNote,
    CrossOrnateNote,
    CircleNote,
    CircleCrossNote,
    CircleDotNote,
    TriangleLeftNote,
    TriangleRightNote,
    TriangleUpNote,
    TriangleDownNote,
    TriangleRoundDownNote,
    DiamondNote,
    MoonNote,
    PlusNote,
    SlashNote,
    SquareNote,
    SlashedBackwardsNote,
    SlashedForwardsNote,

    Fall,
    QuickFall,
    Doit,
    Plop,
    Scoop,
    BrassBend,
    SlideOutDown,
    SlideOutUp,
    SlideInAbove,
    SlideInBelow,
    VolumeSwell,

    Vibrato,
    WideVibrato,
    MoltoVibrato,
    SenzaVibrato,

    Tremolo8th,
    Tremolo16th,
    Tremolo32nd,
    Tremolo64th,
    TremoloBuzz,

    TrillBaroque,
    UpperMordent,
    LowerMordent,
    UpperMordentBaroque,
    LowerMordentBaroque,
    PrallMordent,
    MordentWithUpperPrefix,
    UpMordent,
    DownMordent,
    Tremblement,
    UpPrall,
    PrallUp,
    PrallDown,
    LinePrall,
    Slide,
    Turn,
    InvertedTurn,

    PreAppoggiatura,
    PostAppoggiatura,
    Acciaccatura,

    TremoloBar,
    Distortion,
    Overdrive,
    Slap,
    Pop,

    ContinuousGlissando,

    // multi-note articulations
    Trill,
    Crescendo,
    Diminuendo,
    DiscreteGlissando,
    Legato,
    Pedal,
    Multibend,
    Arpeggio,
    ArpeggioUp,
    ArpeggioDown,
    ArpeggioStraightUp,
    ArpeggioStraightDown,

    Last
};

using ArticulationTypeSet = std::unordered_set<ArticulationType>;

inline bool isMultiNoteArticulation(const ArticulationType type)
{
    static const ArticulationTypeSet MULTI_TYPES = {
        ArticulationType::Trill,
        ArticulationType::Crescendo,
        ArticulationType::Diminuendo,
        ArticulationType::DiscreteGlissando,
        ArticulationType::Legato,
        ArticulationType::Pedal,
        ArticulationType::Multibend,
        ArticulationType::Arpeggio,
        ArticulationType::ArpeggioUp,
        ArticulationType::ArpeggioDown,
        ArticulationType::ArpeggioStraightUp,
        ArticulationType::ArpeggioStraightDown,
    };

    return muse::contains(MULTI_TYPES, type);
}

inline bool isSingleNoteArticulation(const ArticulationType type)
{
    return !isMultiNoteArticulation(type);
}

inline bool isRangedArticulation(const ArticulationType type)
{
    if (isSingleNoteArticulation(type)) {
        return false;
    }

    return type == ArticulationType::Legato
           || type == ArticulationType::Pedal
           || type == ArticulationType::Multibend;
}

static const String ORDINARY_PLAYING_TECHNIQUE_CODE(u"ordinary_technique");

using dynamic_level_t = percentage_t;
constexpr dynamic_level_t MAX_DYNAMIC_LEVEL = HUNDRED_PERCENT;
constexpr dynamic_level_t MIN_DYNAMIC_LEVEL = 0;
constexpr dynamic_level_t DYNAMIC_LEVEL_STEP = 5 * ONE_PERCENT;

enum class DynamicType {
    Undefined = -1,
    ppppppppp = MIN_DYNAMIC_LEVEL,
    pppppppp = static_cast<int>(7.5f * ONE_PERCENT),
    ppppppp = static_cast<int>(12.5f * ONE_PERCENT),
    pppppp = static_cast<int>(17.5f * ONE_PERCENT),
    ppppp = static_cast<int>(22.5f * ONE_PERCENT),
    pppp = static_cast<int>(27.5f * ONE_PERCENT),
    ppp = static_cast<int>(32.5f * ONE_PERCENT),
    pp = static_cast<int>(37.5f * ONE_PERCENT),
    p = static_cast<int>(42.5f * ONE_PERCENT),
    mp = static_cast<int>(47.5f * ONE_PERCENT),
    Natural = 50 * ONE_PERCENT,
    mf = static_cast<int>(52.5f * ONE_PERCENT),
    f = static_cast<int>(57.5f * ONE_PERCENT),
    ff = static_cast<int>(62.5f * ONE_PERCENT),
    fff = static_cast<int>(67.5f * ONE_PERCENT),
    ffff = static_cast<int>(72.5f * ONE_PERCENT),
    fffff = static_cast<int>(77.5f * ONE_PERCENT),
    ffffff = static_cast<int>(82.5f * ONE_PERCENT),
    fffffff = static_cast<int>(87.5f * ONE_PERCENT),
    ffffffff = static_cast<int>(92.5f * ONE_PERCENT),
    fffffffff = MAX_DYNAMIC_LEVEL,
    Last
};

inline DynamicType approximateDynamicType(const dynamic_level_t dynamicLevel)
{
    if (dynamicLevel < MIN_DYNAMIC_LEVEL) {
        return DynamicType::ppppppppp;
    }

    if (dynamicLevel > MAX_DYNAMIC_LEVEL) {
        return DynamicType::fffffffff;
    }

    return static_cast<DynamicType>(dynamicLevel);
}

constexpr inline dynamic_level_t dynamicLevelFromType(const DynamicType type)
{
    if (type == DynamicType::Undefined) {
        return MIN_DYNAMIC_LEVEL;
    }

    return static_cast<dynamic_level_t>(type);
}

struct ArrangementPattern
{
    duration_percentage_t durationFactor = 0;
    duration_percentage_t timestampOffset = 0;

    ArrangementPattern() = default;

    ArrangementPattern(duration_percentage_t _durationFactor, duration_percentage_t _timestampOffset)
        : durationFactor(_durationFactor), timestampOffset(_timestampOffset)
    {
    }

    bool operator==(const ArrangementPattern& other) const
    {
        return durationFactor == other.durationFactor
               && timestampOffset == other.timestampOffset;
    }
};

using ArrangementPatternList = std::vector<ArrangementPattern>;

struct PitchPattern
{
    using PitchOffsetMap = PitchCurve;

    PitchOffsetMap pitchOffsetMap;

    PitchPattern() = default;

    PitchPattern(size_t size, percentage_t step, pitch_level_t defaultValue)
    {
        for (size_t i = 0; i < size; ++i) {
            pitchOffsetMap.emplace(step * static_cast<int>(i), defaultValue);
        }
    }

    pitch_level_t maxAmplitudeLevel() const
    {
        return pitchOffsetMap.maxAmplitudeLevel();
    }

    bool operator==(const PitchPattern& other) const
    {
        return pitchOffsetMap == other.pitchOffsetMap;
    }
};

using PitchPatternList = std::vector<PitchPattern>;

using ExpressionCurve = ValuesCurve<dynamic_level_t>;

struct ExpressionPattern
{
    using DynamicOffsetMap = ExpressionCurve;

    ExpressionCurve dynamicOffsetMap;

    ExpressionPattern() = default;

    ExpressionPattern(size_t size, percentage_t step, dynamic_level_t defaultValue)
    {
        for (size_t i = 0; i < size; ++i) {
            dynamicOffsetMap.emplace(step * static_cast<int>(i), defaultValue);
        }
    }

    dynamic_level_t maxAmplitudeLevel() const
    {
        return dynamicOffsetMap.maxAmplitudeLevel();
    }

    bool operator==(const ExpressionPattern& other) const
    {
        return dynamicOffsetMap == other.dynamicOffsetMap;
    }
};

using ExpressionPatternList = std::vector<ExpressionPattern>;

struct ArticulationPatternSegment
{
    ArrangementPattern arrangementPattern;
    PitchPattern pitchPattern;
    ExpressionPattern expressionPattern;

    ArticulationPatternSegment() = default;

    ArticulationPatternSegment(ArrangementPattern&& arrangement, PitchPattern&& pitch, ExpressionPattern&& expression)
        : arrangementPattern(arrangement), pitchPattern(pitch), expressionPattern(expression)
    {}

    bool operator==(const ArticulationPatternSegment& other) const
    {
        return arrangementPattern == other.arrangementPattern
               && pitchPattern == other.pitchPattern
               && expressionPattern == other.expressionPattern;
    }
};

using ArticulationPattern = SharedMap<duration_percentage_t, ArticulationPatternSegment>;

struct ArticulationsProfile
{
    std::vector<ArticulationFamily> supportedFamilies;

    const ArticulationPattern& pattern(const ArticulationType type) const
    {
        auto search = m_patterns.find(type);

        if (search == m_patterns.cend()) {
            static ArticulationPattern emptyPattern;
            return emptyPattern;
        }

        return search->second;
    }

    void setPattern(const ArticulationType type, const ArticulationPattern& scope)
    {
        m_patterns.insert_or_assign(type, scope);
    }

    void removePattern(const ArticulationType type)
    {
        m_patterns.erase(type);
    }

    const SharedHashMap<ArticulationType, ArticulationPattern>& data() const
    {
        return m_patterns;
    }

    bool contains(const ArticulationType type) const
    {
        return m_patterns.find(type) != m_patterns.cend();
    }

    bool isValid() const
    {
        return !m_patterns.empty();
    }

    bool operator==(const ArticulationsProfile& other) const
    {
        return m_patterns == other.m_patterns;
    }

private:
    SharedHashMap<ArticulationType, ArticulationPattern> m_patterns;
};

using ArticulationsProfilePtr = std::shared_ptr<ArticulationsProfile>;

struct ArticulationMeta
{
    ArticulationType type = ArticulationType::Undefined;
    ArticulationPattern pattern;

    timestamp_t timestamp = 0;
    duration_t overallDuration = 0;
    pitch_level_t overallPitchChangesRange = 0;
    dynamic_level_t overallDynamicChangesRange = 0;

    ArticulationMeta() = default;

    ArticulationMeta(const ArticulationType _type)
        : type(_type)
    {}

    ArticulationMeta(const ArticulationType _type,
                     const ArticulationPattern& _pattern,
                     const timestamp_t _timestamp,
                     const duration_t _duration,
                     const pitch_level_t overallPitchRange = 0,
                     const dynamic_level_t overallDynamicRange = 0)
        : type(_type),
        pattern(_pattern),
        timestamp(_timestamp),
        overallDuration(_duration),
        overallPitchChangesRange(overallPitchRange),
        overallDynamicChangesRange(overallDynamicRange)
    {}

    bool operator==(const ArticulationMeta& other) const
    {
        return type == other.type
               && pattern == other.pattern
               && timestamp == other.timestamp
               && overallDuration == other.overallDuration
               && overallPitchChangesRange == other.overallPitchChangesRange
               && overallDynamicChangesRange == other.overallDynamicChangesRange;
    }
};

using ArticulationMetaMap = SharedHashMap<ArticulationType, ArticulationMeta>;

struct ArticulationAppliedData {
    ArticulationMeta meta;

    ArticulationPatternSegment appliedPatternSegment;

    duration_percentage_t occupiedFrom = 0;
    duration_percentage_t occupiedTo = HUNDRED_PERCENT;

    pitch_level_t occupiedPitchChangesRange = 0;
    dynamic_level_t occupiedDynamicChangesRange = 0;

    ArticulationAppliedData() = default;

    explicit ArticulationAppliedData(ArticulationMeta&& _meta,
                                     const duration_percentage_t _occupiedFrom,
                                     const duration_percentage_t _occupiedTo)
        : meta(std::move(_meta))
    {
        updateOccupiedRange(_occupiedFrom, _occupiedTo);
    }

    explicit ArticulationAppliedData(const ArticulationMeta& _meta,
                                     const duration_percentage_t _occupiedFrom,
                                     const duration_percentage_t _occupiedTo)
        : meta(_meta)
    {
        updateOccupiedRange(_occupiedFrom, _occupiedTo);
    }

    bool operator==(const ArticulationAppliedData& other) const
    {
        return meta == other.meta
               && appliedPatternSegment == other.appliedPatternSegment
               && occupiedFrom == other.occupiedFrom
               && occupiedTo == other.occupiedTo
               && occupiedPitchChangesRange == other.occupiedPitchChangesRange
               && occupiedDynamicChangesRange == other.occupiedDynamicChangesRange;
    }

    void updateOccupiedRange(const duration_percentage_t from, const duration_percentage_t to)
    {
        occupiedFrom = from;
        occupiedTo = to;

        if (meta.pattern.empty()) {
            return;
        }

        if (occupiedFrom == 0 && occupiedTo == HUNDRED_PERCENT) {
            appliedPatternSegment = meta.pattern.cbegin()->second;
            occupiedPitchChangesRange = meta.overallPitchChangesRange;
            occupiedDynamicChangesRange = meta.overallDynamicChangesRange;
            return;
        }

        float occupiedFactor = percentageToFactor(occupiedTo);
        occupiedPitchChangesRange = static_cast<pitch_level_t>(static_cast<float>(meta.overallPitchChangesRange) * occupiedFactor);
        occupiedDynamicChangesRange = static_cast<pitch_level_t>(static_cast<float>(meta.overallDynamicChangesRange) * occupiedFactor);

        const auto& lower = meta.pattern.lower_bound(occupiedFrom);

        if (lower != meta.pattern.cend()) {
            appliedPatternSegment = lower->second;
        } else {
            appliedPatternSegment = meta.pattern.cbegin()->second;
        }
    }
};

struct ArticulationMap : public SharedHashMap<ArticulationType, ArticulationAppliedData>
{
    void updateOccupiedRange(const ArticulationType type, const duration_percentage_t occupiedFrom, const duration_percentage_t occupiedTo)
    {
        if (!contains(type)) {
            return;
        }

        ArticulationAppliedData& data = at(type);
        data.updateOccupiedRange(occupiedFrom, occupiedTo);

        if (occupiedFrom == 0 && occupiedTo == HUNDRED_PERCENT) {
            return;
        }

        preCalculateAverageData();
    }

    duration_percentage_t averageDurationFactor() const
    {
        return m_averageDurationFactor;
    }

    duration_percentage_t averageTimestampOffset() const
    {
        return m_averageTimestampOffset;
    }

    const PitchPattern::PitchOffsetMap& averagePitchOffsetMap() const
    {
        return m_averagePitchOffsetMap;
    }

    pitch_level_t averagePitchRange() const
    {
        return m_averagePitchRange;
    }

    dynamic_level_t averageMaxAmplitudeLevel() const
    {
        return m_averageMaxAmplitudeLevel;
    }

    dynamic_level_t averageDynamicRange() const
    {
        return m_averageDynamicRange;
    }

    const ExpressionPattern::DynamicOffsetMap& averageDynamicOffsetMap() const
    {
        return m_averageDynamicOffsetMap;
    }

    void preCalculateAverageData()
    {
        if (empty()) {
            return;
        }

        if (size() == 1) {
            const ArticulationPatternSegment& segment = cbegin()->second.appliedPatternSegment;

            m_averageDurationFactor = segment.arrangementPattern.durationFactor;
            m_averageTimestampOffset = segment.arrangementPattern.timestampOffset;
            m_averageMaxAmplitudeLevel = segment.expressionPattern.maxAmplitudeLevel();
            m_averagePitchRange = cbegin()->second.occupiedPitchChangesRange;
            m_averageDynamicRange = cbegin()->second.occupiedDynamicChangesRange;
            m_averageDynamicOffsetMap = segment.expressionPattern.dynamicOffsetMap;
            m_averagePitchOffsetMap = segment.pitchPattern.pitchOffsetMap;
            return;
        }

        resetData();

        ParamsSum paramsSum;
        for (size_t i = 0; i < EXPECTED_SIZE; ++i) {
            paramsSum.pitchOffsetMap.insert_or_assign(static_cast<int>(i) * TEN_PERCENT, 0);
            paramsSum.dynamicOffsetMap.insert_or_assign(static_cast<int>(i) * TEN_PERCENT, 0);
        }

        for (auto it = cbegin(); it != cend(); ++it) {
            const ArticulationAppliedData& appliedArticulation = it->second;
            sumUpData(appliedArticulation, paramsSum);
        }

        calculateAverage(paramsSum);
    }

private:
    void resetData()
    {
        m_averageDurationFactor = 0;
        m_averageTimestampOffset = 0;
        m_averageMaxAmplitudeLevel = 0;
        m_averageDynamicRange = 0;
        m_averagePitchRange = 0;
        m_averagePitchOffsetMap.clear();
        m_averageDynamicOffsetMap.clear();
    }

    struct ParamsSum {
        int durationFactor = 0;
        int timestampOffset = 0;
        int maxAmplitudeLevel = 0;
        int pitchRange = 0;
        int dynamicRange = 0;
        ValuesCurve<int> pitchOffsetMap;
        ValuesCurve<int> dynamicOffsetMap;
    };

    void sumUpData(const ArticulationAppliedData& appliedArticulation, ParamsSum& out)
    {
        const ArticulationPatternSegment& segment = appliedArticulation.appliedPatternSegment;

        out.durationFactor += segment.arrangementPattern.durationFactor;
        out.timestampOffset += segment.arrangementPattern.timestampOffset;
        out.maxAmplitudeLevel += segment.expressionPattern.maxAmplitudeLevel();
        out.pitchRange += appliedArticulation.occupiedPitchChangesRange;
        out.dynamicRange += appliedArticulation.occupiedDynamicChangesRange;

        sumUpOffsets(segment, out);
    }

    void sumUpOffsets(const ArticulationPatternSegment& segment, ParamsSum& out)
    {
        auto dynamicOffsetIt = out.dynamicOffsetMap.begin();
        auto pitchOffsetIt = out.pitchOffsetMap.begin();

        auto segmentDynamicOffsetIt = segment.expressionPattern.dynamicOffsetMap.cbegin();
        auto segmentPitchOffsetIt = segment.pitchPattern.pitchOffsetMap.cbegin();

        bool hasMeaningDynamicOffset = segment.expressionPattern.maxAmplitudeLevel() != dynamicLevelFromType(DynamicType::Natural);
        bool hasMeaningPitchOffset = segment.pitchPattern.maxAmplitudeLevel() != 0;

        if (!hasMeaningDynamicOffset && !hasMeaningPitchOffset) {
            return;
        }

        while (segmentDynamicOffsetIt != segment.expressionPattern.dynamicOffsetMap.cend()
               && segmentPitchOffsetIt != segment.pitchPattern.pitchOffsetMap.cend()) {
            if (hasMeaningDynamicOffset) {
                dynamicOffsetIt->second += segmentDynamicOffsetIt->second;
            }

            if (hasMeaningPitchOffset) {
                pitchOffsetIt->second += segmentPitchOffsetIt->second;
            }

            ++dynamicOffsetIt;
            ++pitchOffsetIt;
            ++segmentDynamicOffsetIt;
            ++segmentPitchOffsetIt;
        }
    }

    void calculateAverage(const ParamsSum& paramsSum)
    {
        int count = static_cast<int>(size());

        if (count == 1) {
            return;
        }

        int dynamicChangesCount = 0;
        int pitchChangesCount = 0;
        int timestampChangesCount = 0;

        for (auto it = cbegin(); it != cend(); ++it) {
            dynamic_level_t amplitudeDynamicLevel = it->second.appliedPatternSegment.expressionPattern.maxAmplitudeLevel();
            dynamic_level_t dynamicLevelOffset = std::abs(amplitudeDynamicLevel - dynamicLevelFromType(DynamicType::Natural));

            if (dynamicLevelOffset != 0) {
                dynamicChangesCount++;
            }

            if (it->second.appliedPatternSegment.pitchPattern.maxAmplitudeLevel() != 0) {
                pitchChangesCount++;
            }

            if (it->second.appliedPatternSegment.arrangementPattern.timestampOffset != 0) {
                timestampChangesCount++;
            }
        }

        m_averageDurationFactor = paramsSum.durationFactor / count;

        if (timestampChangesCount > 0) {
            m_averageTimestampOffset = paramsSum.timestampOffset / timestampChangesCount;
        }

        if (dynamicChangesCount > 0) {
            m_averageMaxAmplitudeLevel = paramsSum.maxAmplitudeLevel / dynamicChangesCount;
            m_averageDynamicRange = paramsSum.dynamicRange / dynamicChangesCount;

            for (const auto& pair : paramsSum.dynamicOffsetMap) {
                m_averageDynamicOffsetMap.insert_or_assign(pair.first, pair.second / dynamicChangesCount);
            }
        } else if (dynamicChangesCount == 0) {
            m_averageMaxAmplitudeLevel = cbegin()->second.appliedPatternSegment.expressionPattern.maxAmplitudeLevel();
            m_averageDynamicRange = cbegin()->second.meta.overallDynamicChangesRange;
            m_averageDynamicOffsetMap = cbegin()->second.appliedPatternSegment.expressionPattern.dynamicOffsetMap;
        }

        if (pitchChangesCount > 0) {
            m_averagePitchRange = paramsSum.pitchRange / pitchChangesCount;

            for (const auto& pair : paramsSum.pitchOffsetMap) {
                m_averagePitchOffsetMap.insert_or_assign(pair.first, pair.second / pitchChangesCount);
            }
        } else if (pitchChangesCount == 0) {
            m_averagePitchRange = cbegin()->second.meta.overallPitchChangesRange;
            m_averagePitchOffsetMap = cbegin()->second.appliedPatternSegment.pitchPattern.pitchOffsetMap;
        }
    }

    duration_percentage_t m_averageDurationFactor = HUNDRED_PERCENT;
    duration_percentage_t m_averageTimestampOffset = 0;
    pitch_level_t m_averagePitchRange = 0;
    dynamic_level_t m_averageMaxAmplitudeLevel = 0;
    dynamic_level_t m_averageDynamicRange = 0;
    PitchPattern::PitchOffsetMap m_averagePitchOffsetMap;
    ExpressionPattern::DynamicOffsetMap m_averageDynamicOffsetMap;
};
}

#endif // MUSE_MPE_MPETYPES_H
