#include "CParagraph.h"
#include <algorithm>

CParagraph::CParagraph()
{
    m_equivalenceMap = { 
            {"one", 1},
            {"two", 2},
            {"three", 3},
            {"four", 4},
            {"five", 5},
            {"six", 6},
            {"seven", 7},
            {"eight", 8},
            {"nine", 9},
            {"ten", 10},
            {"eleven", 11},
            {"twelve", 12},
            {"thirteen", 13},
            {"fourteen", 14},
            {"fifteen", 15},
            {"sixteen", 16},
            {"seventeen", 17},
            {"eighteen", 18},
            {"nineteen", 19},

            {"twenty", 20},
            {"thirty", 30},
            {"forty", 40},
            {"fifty", 50},
            {"sixty", 60},
            {"seventy", 70},
            {"eighty", 80},
            {"ninety", 90},

            {"hundred", 100},
            {"thousand", 1'000},
            {"million", 1'000'000},
			{"billion", 1'000'000'000}};
}

void 
CParagraph::TraverseParagraph(string& paragraph)
{
    string word{}, previousWord{};
    
    paragraph += " ."; //last delimiter

    string delimeters{ " ,.-':;?()+*/%$#!\"@^&\n" };

    size_t initPosWord{0}, endPosWord{0};
    size_t initPosNumber{0}, endPosNumber{0};
    bool insideNumber{};

    while ((endPosWord = paragraph.find_first_of(delimeters, initPosWord)) != std::string::npos)
    {
        previousWord = word;
        word = paragraph.substr(initPosWord, endPosWord - initPosWord);

        //convert the word to lowercase to check the map
        std::transform(word.begin(), word.end(), word.begin(),
            [](unsigned char c) { return std::tolower(c); });

        //value is zero if the word does not exist in the map
        size_t value{0};
        bool initPosIsModified{};
        value = m_equivalenceMap[word];

        if (word == "and" && previousWord == "hundred")
        {
            //do nothing. It is a correct "and" inside a number
        }
        else if (value != 0)
        {
            m_vectorNumbers.push_back(value);

            if (not insideNumber)
            {
                initPosNumber = initPosWord;
                insideNumber = true;
            }
            endPosNumber = endPosWord;
        }
        else
        {
            if (m_vectorNumbers.size() > 0)
            {
				//This number could be splited with commas also (lack of time) 
                size_t totalNumber = GetNumberInDigits(m_vectorNumbers);
				
                paragraph.replace(initPosNumber, endPosNumber - initPosNumber, to_string(totalNumber));
                size_t difference = (endPosNumber - initPosNumber) - to_string(totalNumber).size();
                initPosWord = initPosWord - difference + to_string(totalNumber).size() - 1;

                endPosWord = 0;

                initPosIsModified = true;
                insideNumber = false;
                m_vectorNumbers.clear();
            }
        }
        if (not initPosIsModified) 
            initPosWord += word.size() + 1; //next word
    }

	paragraph.erase(paragraph.size()-2, 2); //remove last delimiter
}

size_t 
CParagraph::GetNumberInDigits(const vector<size_t> vNumbers)
{
    //Loop the vector and get the last ocurrence of billion, million, thousand and hundred
    bool hasBillion{}, hasMillion{}, hasThousand{}, hasHundred{};
    size_t indexBillion{0}, indexMillion{0}, indexThousand{0}, indexHundred{0};
    size_t countElements{0};

    for (auto number : vNumbers)
    {
        countElements++;
		if (number == m_equivalenceMap["billion"])
        {
            indexBillion = indexMillion = indexThousand = indexHundred = countElements;
            hasBillion = true;
            hasMillion = hasThousand = hasHundred = false;
        } 
		
        if (number == m_equivalenceMap["million"])
        {
            indexMillion = indexThousand = indexHundred = countElements;
            hasMillion = true;
            hasThousand = hasHundred = false;
        }
        else if (number == m_equivalenceMap["thousand"])
        {
            if (countElements > indexMillion)
            {
                indexThousand = indexHundred = countElements;
                hasThousand = true;
                hasHundred = false;
            }
        }
        else if (number == m_equivalenceMap["hundred"])
        {
            if (countElements > indexThousand)
            {
                indexHundred = countElements;
                hasHundred = true;
            }
        }
    }

    //Multiply all the numbers that are in the left position for million, thousand and/or hundred
    //considering if the previous value is higher or not 
    size_t previousMultiplier{0};
    
	//For billion is fixed to 10^9 directly.
	if (hasBillion)
		return m_equivalenceMap["billion"];
	
    //For million
    size_t totalMillion{1};
    if (hasMillion)
    {
        for (size_t i = 0; i < indexMillion; i++)
        {
            if (previousMultiplier > vNumbers[i])
            {
                if (previousMultiplier != 0)
                    totalMillion += vNumbers[i];
            }
            else
                totalMillion *= vNumbers[i];

            previousMultiplier = vNumbers[i];
        }

    }
    else
        totalMillion = 0;

    //For thousand
    previousMultiplier = 0;
    size_t totalThousand = 1;
    if (hasThousand)
    {
        if (hasMillion)
        {
            for (size_t i = indexMillion; i < indexThousand; i++)
            {
                if (previousMultiplier > vNumbers[i])
                {
                    if (previousMultiplier != 0)
                        totalThousand += vNumbers[i];
                }
                else
                    totalThousand *= vNumbers[i];

                previousMultiplier = vNumbers[i];
            }
        }
        else
        {
            for (size_t i = 0; i < indexThousand; i++)
            {
                if (previousMultiplier > vNumbers[i])
                {
                    if (previousMultiplier != 0)
                        totalThousand += vNumbers[i];
                }
                else
                    totalThousand *= vNumbers[i];

                previousMultiplier = vNumbers[i];
            }
        }
    }
    else
        totalThousand = 0;

    //For hundred
    previousMultiplier = 0;
    size_t totalHundred = 1;
    if (hasHundred)
    {
        if (hasThousand)
        {
            for (size_t i = indexThousand; i < indexHundred; i++)
            {
                if (previousMultiplier > vNumbers[i])
                {
                    if (previousMultiplier != 0)
                        totalHundred += vNumbers[i];
                }
                else
                    totalHundred *= vNumbers[i];

                previousMultiplier = vNumbers[i];
            }
        }
        else if (hasMillion)
        {
            for (size_t i = indexMillion; i < indexHundred; i++)
            {
                if (previousMultiplier > vNumbers[i])
                {
                    if (previousMultiplier != 0)
                        totalHundred += vNumbers[i];
                }
                else
                    totalHundred *= vNumbers[i];

                previousMultiplier = vNumbers[i];
            }
        }
        else
        {
            for (size_t i = 0; i < indexHundred; i++)
            {
                if (previousMultiplier > vNumbers[i])
                {
                    if (previousMultiplier != 0)
                        totalHundred += vNumbers[i];
                }
                else
                    totalHundred *= vNumbers[i];

                previousMultiplier = vNumbers[i];
            }
        }
    }
    else
        totalHundred = 0;

    //For the rest values
    size_t totalRest{0};
    size_t vectorSize = vNumbers.size();
    if (not (indexMillion == vectorSize || indexThousand == vectorSize || indexHundred == vectorSize))
    {
        for (size_t i = indexHundred; i < vNumbers.size(); i++)
        {
            totalRest += vNumbers[i];
        }
    }

    return totalMillion + totalThousand + totalHundred + totalRest;
}

