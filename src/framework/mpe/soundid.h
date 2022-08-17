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

#ifndef MU_MPE_SOUNDID_H
#define MU_MPE_SOUNDID_H

#include <set>
#include <unordered_map>

#include "types/string.h"

namespace mu::mpe {
enum class SoundId
{
    Undefined = -1,

    Accordion,
    Bandoneon,
    Concertina,
    Harmonica,
    Melodica,
    Sheng,
    Celesta,
    Clavichord,
    Harpsichord,
    Virginal,
    Piano,
    Organ,
    Harmonium,
    Synthesizer,
    Theremin,
    OndesMartenot,

    Harp,
    Cavaquinho,
    Guitar,
    BassGuitar,
    Banjo,
    Ukulele,
    Mandolin,
    MtnDulcimer,
    Lute,
    Theorbo,
    Archlute,
    Balalaika,
    Koto,
    Oud,
    Shamisen,
    Sitar,
    Prim,
    Brac,
    Bugarija,
    Berda,
    Celo,
    Bandurria,
    Laud,
    StringsGroup,
    Violin,
    ViolinSection,
    Viola,
    ViolaDaGamba,
    ViolaSection,
    Violoncello,
    VioloncelloSection,
    Viol,
    PardessusViol,
    Baryton,
    Violone,
    Nyckelharpa,
    Erhu,
    Contrabass,
    ContrabassSection,
    Octobass,

    WindsGroup,
    Piccolo,
    Heckelphone,
    HeckelphoneClarinet,
    Oboe,
    Lupophone,
    Flute,
    PanFlute,
    Danso,
    Traverso,
    Dizi,
    Shakuhachi,
    Fife,
    Whistle,
    Flageolet,
    Recorder,
    Ocarina,
    Gemshorn,
    Quena,
    Horn,
    Bassethorn,
    Shawm,
    Cromorne,
    Crumhorn,
    Cornamuse,
    Kelhorn,
    Rauschpfeife,
    Duduk,
    Shenai,
    Clarinet,
    Chalumeau,
    Xaphoon,
    Tarogato,
    Octavin,
    Saxophone,
    Aulochrome,
    Bassoon,
    Contrabassoon,
    Dulcian,
    Rackett,
    Sarrusophone,
    Bagpipe,
    Tuba,
    Cornet,
    Posthorn,
    BrassGroup,
    Trumpet,
    Bugle,
    MellophoneBugle,
    EuphoniumBugle,
    Euphonium,
    Fiscorn,
    Flugelhorn,
    Kuhlohorn,
    Ophicleide,
    Cornettino,
    Cornett,
    Serpent,
    Trombone,
    Cimbasso,
    Sackbut,
    Sousaphone,
    Helicon,
    Conch,
    Saxhorn,
    Horagai,
    Alphorn,
    RagDung,
    Didgeridoo,
    Shofar,
    Vuvuzela,

    Timpani,
    RotoToms,
    Tubaphone,
    SteelDrums,
    Glockenspiel,
    Xylophone,
    Xylomarimba,
    Vibraphone,
    Dulcimer,
    Cimbalom,
    Marimba,
    Crotales,
    Chimes,
    Carillon,
    Gong,
    Metallophone,
    Flexatone,
    MusicalSaw,
    MusicalGlasses,
    KlaxonHorns,
    Kalimba,
    Bongos,
    TomToms,
    Conga,
    Cuica,
    Drumset,
    Drum,
    Tablas,
    Timbales,
    Anvil,
    Bell,
    Chain,
    Cymbal,
    HiHat,
    Pipe,
    Castanet,
    TamTam,
    Thundersheet,
    Triangle,
    Claves,
    Guiro,
    Block,
    Cabasa,
    Maraca,
    Quijada,
    Ratchet,
    Shaker,
    Stones,
    Tambourine,
    Tubo,
    Vibraslap,
    Whip,
    Snap,
    Clap,
    Slap,
    Stamp,
    Choir,
    Kazoo
};

enum class SoundCategory
{
    Undefined = -1,
    Keyboards,
    Strings,
    Winds,
    Percussions,
    Voices
};

enum class SoundSubCategory
{
    Undefined = -1,

    English,
    Armenian,
    Alpine,
    Australian,
    Irish,
    French,
    Chinese,
    Vienna,
    Greek,
    Japanese,
    Tibetan,
    African,
    Indian,
    Spanish,
    Swedish,
    Hungarian,
    Romanian,
    CentralEuropean,

    Baroque,
    Classical,
    Modern,
    Orchestral,

    Hammond,
    Wagner,
    Orff,
    Huang,
    Hohner,

    Percussive,
    Piped,
    Rotary,
    Reed,
    Foot,
    Hand,
    Finger,
    Boy,
    Girl,
    Male,
    Female,
    Pad,

    Temple,
    Military,
    Ride,
    Sleigh,
    Cow,
    Marching,

    Splash,
    Crash,
    Plate,
    Bowl,
    Frame,
    Slit,
    Field,
    Snare,
    Brake,
    Slide,
    Pocket,
    Garklein,
    Toy,
    String,
    TwelveString,

    Grand,
    HonkyTonk,
    Upright,
    Prima,
    Secunda,

    Electric,
    Acoustic,
    Pedal,
    Steel,
    Metal,
    Iron,
    Brass,
    Tin,
    Nylon,
    Wooden,
    Sandpaper,
    Glass,
    Shell,
    Wind,

    Treble,
    Diatonic,
    Chromatic,
    Octave,

    Piccolo,
    Alto,
    Tenor,
    Baritone,
    Soprano,
    Mezzo_Soprano,
    Sopranino,
    Sopranissimo,
    Counter_Tenor,
    Contra,
    Contra_Alto,
    Sub_Contra_Alto,
    Contra_Bass,
    Sub_Contra_Bass,
    Double_Contra_Bass,
    Bass,
    Bowed,
    Great_Bass,
    Hyper_Bass,
    Melody,

    FX_Goblins,
    FX_Atmosphere,
    FX_Brightness,
    FX_Crystal,
    FX_Echoes,
    FX_Rain,
    FX_SciFi,
    FX_SoundTrack,

    Sweep,
    Warm,
    NewAge,
    Polysynth,
    Halo,
    Metallic,
    Choir,

    Sine_Wave,
    Square_Wave,
    Sawtooth_Wave,
};

static const String UNDEFINED_STR(u"Undefined");

inline const String& soundIdToString(const SoundId id)
{
    static const std::unordered_map<SoundId, String> ID_STRINGS
    {
        { SoundId::Accordion, String("Accordion") },
        { SoundId::Bandoneon, String("Bandoneon") },
        { SoundId::Concertina, String("Concertina") },
        { SoundId::Harmonica, String("Harmonica") },
        { SoundId::Melodica, String("Melodica") },
        { SoundId::Sheng, String("Sheng") },
        { SoundId::Celesta, String("Celesta") },
        { SoundId::Clavichord, String("Clavichord") },
        { SoundId::Harpsichord, String("Harpsichord") },
        { SoundId::Virginal, String("Virginal") },
        { SoundId::Piano, String("Piano") },
        { SoundId::Organ, String("Organ") },
        { SoundId::Harmonium, String("Harmonium") },
        { SoundId::Synthesizer, String("Synthesizer") },
        { SoundId::Theremin, String("Theremin") },
        { SoundId::OndesMartenot, String("OndesMartenot") },

        { SoundId::Harp, String("Harp") },
        { SoundId::Cavaquinho, String("Cavaquinho") },
        { SoundId::Guitar, String("Guitar") },
        { SoundId::BassGuitar, String("BassGuitar") },
        { SoundId::Banjo, String("Banjo") },
        { SoundId::Ukulele, String("Ukulele") },
        { SoundId::Mandolin, String("Mandolin") },
        { SoundId::MtnDulcimer, String("MtnDulcimer") },
        { SoundId::Lute, String("Lute") },
        { SoundId::Theorbo, String("Theorbo") },
        { SoundId::Archlute, String("Archlute") },
        { SoundId::Balalaika, String("Balalaika") },
        { SoundId::Koto, String("Koto") },
        { SoundId::Oud,String( "Oud") },
        { SoundId::Shamisen, String("Shamisen") },
        { SoundId::Sitar, String("Sitar") },
        { SoundId::Prim, String("Prim") },
        { SoundId::Brac, String("Brac") },
        { SoundId::Bugarija, String("Bugarija") },
        { SoundId::Berda, String("Berda") },
        { SoundId::Celo, String("Celo") },
        { SoundId::Bandurria, String("Bandurria") },
        { SoundId::Laud, String("Laud") },
        { SoundId::StringsGroup, String("StringsGroup") },
        { SoundId::Violin, String("Violin") },
        { SoundId::ViolinSection, String("ViolinSection") },
        { SoundId::Viola, String("Viola") },
        { SoundId::ViolaDaGamba, String("ViolaDaGamba") },
        { SoundId::ViolaSection, String("ViolaSection") },
        { SoundId::Violoncello, String("Violoncello") },
        { SoundId::VioloncelloSection, String("VioloncelloSection") },
        { SoundId::Viol, String("Viol") },
        { SoundId::PardessusViol, String("PardessusViol") },
        { SoundId::Baryton, String("Baryton") },
        { SoundId::Violone, String("Violone") },
        { SoundId::Nyckelharpa, String("Nyckelharpa") },
        { SoundId::Erhu, String("Erhu") },
        { SoundId::Contrabass, String("Contrabass") },
        { SoundId::ContrabassSection, String("ContrabassSection") },
        { SoundId::Octobass, String("Octobass") },

        { SoundId::WindsGroup, String("WindsGroup") },
        { SoundId::Piccolo, String("Piccolo") },
        { SoundId::Heckelphone, String("Heckelphone") },
        { SoundId::HeckelphoneClarinet, String("HeckelphoneClarinet") },
        { SoundId::Oboe, String("Oboe") },
        { SoundId::Lupophone, String("Lupophone") },
        { SoundId::Flute, String("Flute") },
        { SoundId::PanFlute, String("PanFlute") },
        { SoundId::Danso, String("Danso") },
        { SoundId::Traverso, String("Traverso") },
        { SoundId::Dizi, String("Dizi") },
        { SoundId::Shakuhachi, String("Shakuhachi") },
        { SoundId::Fife, String("Fife") },
        { SoundId::Whistle, String("Whistle") },
        { SoundId::Flageolet, String("Flageolet") },
        { SoundId::Recorder, String("Recorder") },
        { SoundId::Ocarina, String("Ocarina") },
        { SoundId::Gemshorn, String("Gemshorn") },
        { SoundId::Quena, String("Quena") },
        { SoundId::Horn, String("Horn") },
        { SoundId::Bassethorn, String("Bassethorn") },
        { SoundId::Shawm, String("Shawm") },
        { SoundId::Cromorne, String("Cromorne") },
        { SoundId::Crumhorn, String("Crumhorn") },
        { SoundId::Cornamuse, String("Cornamuse") },
        { SoundId::Kelhorn, String("Kelhorn") },
        { SoundId::Rauschpfeife, String("Rauschpfeife") },
        { SoundId::Duduk, String("Duduk") },
        { SoundId::Shenai, String("Shenai") },
        { SoundId::Clarinet, String("Clarinet") },
        { SoundId::Chalumeau, String("Chalumeau") },
        { SoundId::Xaphoon, String("Xaphoon") },
        { SoundId::Tarogato, String("Tarogato") },
        { SoundId::Octavin,String( "Octavin") },
        { SoundId::Saxophone, String("Saxophone") },
        { SoundId::Aulochrome, String("Aulochrome") },
        { SoundId::Bassoon, String("Bassoon") },
        { SoundId::Contrabassoon, String("Contrabassoon") },
        { SoundId::Dulcian, String("Dulcian") },
        { SoundId::Rackett, String("Rackett") },
        { SoundId::Sarrusophone, String("Sarrusophone") },
        { SoundId::Bagpipe, String("Bagpipe") },
        { SoundId::Tuba, String("Tuba") },
        { SoundId::Cornet, String("Cornet") },
        { SoundId::Posthorn, String("Posthorn") },
        { SoundId::BrassGroup, String("BrassGroup") },
        { SoundId::Trumpet, String("Trumpet") },
        { SoundId::Bugle, String("Bugle") },
        { SoundId::MellophoneBugle, String("MellophoneBugle") },
        { SoundId::EuphoniumBugle, String("EuphoniumBugle") },
        { SoundId::Euphonium, String("Euphonium") },
        { SoundId::Fiscorn, String("Fiscorn") },
        { SoundId::Flugelhorn, String("Flugelhorn") },
        { SoundId::Kuhlohorn, String("Kuhlohorn") },
        { SoundId::Ophicleide, String("Ophicleide") },
        { SoundId::Cornettino, String("Cornettino") },
        { SoundId::Cornett, String("Cornett") },
        { SoundId::Serpent, String("Serpent") },
        { SoundId::Trombone, String("Trombone") },
        { SoundId::Cimbasso, String("Cimbasso") },
        { SoundId::Sackbut, String("Sackbut") },
        { SoundId::Sousaphone, String("Sousaphone") },
        { SoundId::Helicon, String("Helicon") },
        { SoundId::Conch, String("Conch") },
        { SoundId::Saxhorn, String("Saxhorn") },
        { SoundId::Horagai, String("Horagai") },
        { SoundId::Alphorn, String("Alphorn") },
        { SoundId::RagDung, String("RagDung") },
        { SoundId::Didgeridoo, String("Didgeridoo") },
        { SoundId::Shofar, String("Shofar") },
        { SoundId::Vuvuzela, String("Vuvuzela") },

        { SoundId::Timpani, String("Timpani") },
        { SoundId::RotoToms, String("RotoToms") },
        { SoundId::Tubaphone, String("Tubaphone") },
        { SoundId::SteelDrums, String("SteelDrums") },
        { SoundId::Glockenspiel, String("Glockenspiel") },
        { SoundId::Xylophone, String("Xylophone") },
        { SoundId::Xylomarimba, String("Xylomarimba") },
        { SoundId::Vibraphone, String("Vibraphone") },
        { SoundId::Dulcimer, String("Dulcimer") },
        { SoundId::Cimbalom, String("Cimbalom") },
        { SoundId::Marimba, String("Marimba") },
        { SoundId::Crotales, String("Crotales") },
        { SoundId::Chimes, String("Chimes") },
        { SoundId::Carillon, String("Carillon") },
        { SoundId::Gong, String("Gong") },
        { SoundId::Metallophone, String("Metallophone") },
        { SoundId::Flexatone, String("Flexatone") },
        { SoundId::MusicalSaw, String("MusicalSaw") },
        { SoundId::MusicalGlasses, String("MusicalGlasses") },
        { SoundId::KlaxonHorns, String("KlaxonHorns") },
        { SoundId::Kalimba, String("Kalimba") },
        { SoundId::Bongos, String("Bongos") },
        { SoundId::TomToms, String("TomToms") },
        { SoundId::Conga, String("Conga") },
        { SoundId::Cuica, String("Cuica") },
        { SoundId::Drumset, String("Drumset") },
        { SoundId::Drum, String("Drum") },
        { SoundId::Tablas, String("Tablas") },
        { SoundId::Timbales, String("Timbales") },
        { SoundId::Anvil, String("Anvil") },
        { SoundId::Bell, String("Bell") },
        { SoundId::Chain, String("Chain") },
        { SoundId::Cymbal, String("Cymbal") },
        { SoundId::HiHat, String("HiHat") },
        { SoundId::Pipe, String("Pipe") },
        { SoundId::Castanet, String("Castanet") },
        { SoundId::TamTam, String("TamTam") },
        { SoundId::Thundersheet, String("Thundersheet") },
        { SoundId::Triangle, String("Triangle") },
        { SoundId::Claves, String("Claves") },
        { SoundId::Guiro, String("Guiro") },
        { SoundId::Block, String("Block") },
        { SoundId::Cabasa, String("Cabasa") },
        { SoundId::Maraca, String("Maraca") },
        { SoundId::Quijada, String("Quijada") },
        { SoundId::Ratchet, String("Ratchet") },
        { SoundId::Shaker, String("Shaker") },
        { SoundId::Stones, String("Stones") },
        { SoundId::Tambourine, String("Tambourine") },
        { SoundId::Tubo, String("Tubo") },
        { SoundId::Vibraslap, String("Vibraslap") },
        { SoundId::Whip, String("Whip") },
        { SoundId::Snap, String("Snap") },
        { SoundId::Clap, String("Clap") },
        { SoundId::Slap, String("Slap") },
        { SoundId::Stamp, String("Stamp") },
        { SoundId::Choir, String("Choir") },
        { SoundId::Kazoo, String("Kazoo") }
    };

    auto search = ID_STRINGS.find(id);
    if (search == ID_STRINGS.cend()) {
        return UNDEFINED_STR;
    }

    return search->second;
}

inline const String& soundCategoryToString(const SoundCategory category)
{
    static const std::unordered_map<SoundCategory, String> CATEGORY_STRINGS
    {
        { SoundCategory::Keyboards, String("Keyboards") },
        { SoundCategory::Strings, String("Strings") },
        { SoundCategory::Winds, String("Winds") },
        { SoundCategory::Percussions, String("Percussions") },
        { SoundCategory::Voices, String("Voices") }
    };

    auto search = CATEGORY_STRINGS.find(category);
    if (search == CATEGORY_STRINGS.cend()) {
        return UNDEFINED_STR;
    }

    return search->second;
}

inline const String& soundSubCategoryToString(const SoundSubCategory& subCategory)
{
    static const std::unordered_map<SoundSubCategory, String> SUBCATEGORY_STRINGS
    {
        { SoundSubCategory::English, String("English") },
        { SoundSubCategory::Armenian, String("Armenian") },
        { SoundSubCategory::Alpine, String("Alpine") },
        { SoundSubCategory::Australian, String("Australian") },
        { SoundSubCategory::Irish, String("Irish") },
        { SoundSubCategory::French, String("French") },
        { SoundSubCategory::Chinese, String("Chinese") },
        { SoundSubCategory::Vienna, String("Vienna") },
        { SoundSubCategory::Greek, String("Greek") },
        { SoundSubCategory::Japanese, String("Japanese") },
        { SoundSubCategory::Tibetan, String("Tibetan") },
        { SoundSubCategory::African, String("African") },
        { SoundSubCategory::Indian, String("Indian") },
        { SoundSubCategory::Spanish, String("Spanish") },
        { SoundSubCategory::Swedish, String("Swedish") },
        { SoundSubCategory::Hungarian, String("Hungarian") },
        { SoundSubCategory::Romanian, String("Romanian") },
        { SoundSubCategory::CentralEuropean, String("CentralEuropean") },

        { SoundSubCategory::Baroque, String("Baroque") },
        { SoundSubCategory::Classical, String("Classical") },
        { SoundSubCategory::Modern, String("Modern") },
        { SoundSubCategory::Orchestral, String("Orchestral") },

        { SoundSubCategory::Hammond, String("Hammond") },
        { SoundSubCategory::Wagner, String("Wagner") },
        { SoundSubCategory::Orff, String("Orff") },
        { SoundSubCategory::Huang, String("Huang") },
        { SoundSubCategory::Hohner, String("Hohner") },

        { SoundSubCategory::Percussive, String("Percussive") },
        { SoundSubCategory::Piped, String("Piped") },
        { SoundSubCategory::Rotary, String("Rotary") },
        { SoundSubCategory::Reed, String("Reed") },
        { SoundSubCategory::Foot, String("Foot") },
        { SoundSubCategory::Hand, String("Hand") },
        { SoundSubCategory::Finger, String("Finger") },
        { SoundSubCategory::Boy, String("Boy") },
        { SoundSubCategory::Girl, String("Girl") },
        { SoundSubCategory::Male, String("Male") },
        { SoundSubCategory::Female, String("Female") },

        { SoundSubCategory::Temple, String("Temple") },
        { SoundSubCategory::Military, String("Military") },
        { SoundSubCategory::Ride, String("Ride") },
        { SoundSubCategory::Sleigh, String("Sleigh") },
        { SoundSubCategory::Cow, String("Cow") },
        { SoundSubCategory::Marching, String("Marching") },

        { SoundSubCategory::Splash, String("Splash") },
        { SoundSubCategory::Crash, String("Crash") },
        { SoundSubCategory::Plate, String("Plate") },
        { SoundSubCategory::Bowl, String("Bowl") },
        { SoundSubCategory::Frame, String("Frame") },
        { SoundSubCategory::Slit, String("Slit") },
        { SoundSubCategory::Field, String("Field") },
        { SoundSubCategory::Snare, String("Snare") },
        { SoundSubCategory::Brake, String("Brake") },
        { SoundSubCategory::Slide, String("Slide") },
        { SoundSubCategory::Pocket, String("Pocket") },
        { SoundSubCategory::Garklein, String("Garklein") },
        { SoundSubCategory::Toy, String("Toy") },
        { SoundSubCategory::TwelveString, String("TwelveString") },

        { SoundSubCategory::Grand, String("Grand") },
        { SoundSubCategory::HonkyTonk, String("HonkyTonk") },
        { SoundSubCategory::Upright, String("Upright") },
        { SoundSubCategory::Prima, String("Prima") },
        { SoundSubCategory::Secunda, String("Secunda") },

        { SoundSubCategory::Electric, String("Electric") },
        { SoundSubCategory::Acoustic, String("Acoustic") },
        { SoundSubCategory::Pedal, String("Pedal") },
        { SoundSubCategory::Steel, String("Steel") },
        { SoundSubCategory::Metal, String("Metal") },
        { SoundSubCategory::Iron, String("Iron") },
        { SoundSubCategory::Brass, String("Brass") },
        { SoundSubCategory::Tin, String("Tin") },
        { SoundSubCategory::Nylon, String("Nylon") },
        { SoundSubCategory::Wooden, String("Wooden") },
        { SoundSubCategory::Sandpaper, String("Sandpaper") },
        { SoundSubCategory::Glass, String("Glass") },
        { SoundSubCategory::Shell, String("Shell") },
        { SoundSubCategory::Wind, String("Wind") },

        { SoundSubCategory::Treble, String("Treble") },
        { SoundSubCategory::Diatonic, String("Diatonic") },
        { SoundSubCategory::Chromatic, String("Chromatic") },
        { SoundSubCategory::Octave, String("Octave") },

        { SoundSubCategory::Piccolo, String("Piccolo") },
        { SoundSubCategory::Alto, String("Alto") },
        { SoundSubCategory::Tenor, String("Tenor") },
        { SoundSubCategory::Baritone, String("Baritone") },
        { SoundSubCategory::Soprano, String("Soprano") },
        { SoundSubCategory::Mezzo_Soprano, String("Mezzo_Soprano") },
        { SoundSubCategory::Sopranino, String("Sopranino") },
        { SoundSubCategory::Sopranissimo, String("Sopranissimo") },
        { SoundSubCategory::Counter_Tenor, String("Counter_Tenor") },
        { SoundSubCategory::Contra, String("Contra") },
        { SoundSubCategory::Contra_Alto, String("Contra_Alto") },
        { SoundSubCategory::Sub_Contra_Alto, String("Sub_Contra_Alto") },
        { SoundSubCategory::Contra_Bass, String("Contra_Bass") },
        { SoundSubCategory::Sub_Contra_Bass, String("Sub_Contra_Bass") },
        { SoundSubCategory::Double_Contra_Bass, String("Double_Contra_Bass") },
        { SoundSubCategory::Bass, String("Bass") },
        { SoundSubCategory::Great_Bass, String("Great_Bass") },
        { SoundSubCategory::Hyper_Bass, String("Hyper_Bass") },
        { SoundSubCategory::Melody, String("Melody") },

        { SoundSubCategory::FX_Goblins, String("FX_Goblins") },
        { SoundSubCategory::FX_Atmosphere, String("FX_Atmosphere") },
        { SoundSubCategory::FX_Brightness, String("FX_Brightness") },
        { SoundSubCategory::FX_Crystal, String("FX_Crystal") },
        { SoundSubCategory::FX_Echoes, String("FX_Echoes") },
        { SoundSubCategory::FX_Rain, String("FX_Rain") },
        { SoundSubCategory::FX_SciFi, String("FX_SciFi") },
        { SoundSubCategory::FX_SoundTrack, String("FX_SoundTrack") }
    };

    auto search = SUBCATEGORY_STRINGS.find(subCategory);
    if (search == SUBCATEGORY_STRINGS.cend()) {
        return UNDEFINED_STR;
    }

    return search->second;
}

using SoundCategories = std::set<SoundCategory>;
struct SoundSubCategories : public std::set<SoundSubCategory>
{
    SoundSubCategories() = default;
    SoundSubCategories(std::initializer_list<SoundSubCategory> initList)
        : std::set<SoundSubCategory>(std::move(initList))
    {
    }

    String toString() const
    {
        StringList subCategoryStrList;
        for (const auto& subCategory : *this) {
            subCategoryStrList.push_back(soundSubCategoryToString(subCategory));
        }

        return subCategoryStrList.join(u",");
    }
};
}

#endif // MU_MPE_SOUNDID_H
