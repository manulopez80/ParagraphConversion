#include "gtest/gtest.h"
#include "CParagraph.h"

TEST(ParagraphTest, Empty) 
{
	CParagraph paragraph;
	string source = " ";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, " ");
}



TEST(ParagraphTest, NoNumberWords) 
{
	CParagraph paragraph;
	string source = "how are you?";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "how are you?");
}


TEST(ParagraphTest, UnitsAlone) 
{
	CParagraph paragraph;
	string source = "two";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "2");
}

TEST(ParagraphTest, UnitsAloneUpperAndLower) 
{
	CParagraph paragraph;
	string source = "seVEn";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "7");
}


TEST(ParagraphTest, UnitsAtBeginning) 
{
	CParagraph paragraph;
	string source = "Two dogs I have";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "2 dogs I have");
}

TEST(ParagraphTest, UnitsAtTheEnd) 
{
	CParagraph paragraph;
	string source = "I have two";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 2");
}

TEST(ParagraphTest, UnitsInTheMiddle) 
{
	CParagraph paragraph;
	string source = "I have two dogs";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 2 dogs");
}

TEST(ParagraphTest, UnitsTwice) 
{
	CParagraph paragraph;
	string source = "I have one dog and one cat";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 1 dog and 1 cat");
}


TEST(ParagraphTest, Dozens) 
{
	CParagraph paragraph;
	string source = "I have eleven cats";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 11 cats");
}

TEST(ParagraphTest, Hundreds_1) 
{
	CParagraph paragraph;
	string source = "I have five hundred dollars";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 500 dollars");
}

TEST(ParagraphTest, Hundreds_2) 
{
	CParagraph paragraph;
	string source = "I have two hundred and sixty nine dollars";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 269 dollars");
}

TEST(ParagraphTest, HundredsTwice) 
{
	CParagraph paragraph;
	string source = "I have nine hundred balls and three hundred and twelve pens";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 900 balls and 312 pens");
}

TEST(ParagraphTest, Thousands_1) 
{
	CParagraph paragraph;
	string source = "I have one thousand ideas";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 1000 ideas");
}

TEST(ParagraphTest, Thousands_2) 
{
	CParagraph paragraph;
	string source = "I have five thousand eight hundred and seventy one dollars";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 5871 dollars");
}

TEST(ParagraphTest, Millions_1) 
{
	CParagraph paragraph;
	string source = "Four million";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "4000000");
}

TEST(ParagraphTest, Millions_2) 
{
	CParagraph paragraph;
	string source = "I have one million three thousand five hundred dollars";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 1003500 dollars");
}

TEST(ParagraphTest, Billion) 
{
	CParagraph paragraph;
	string source = "I have one billion dollars";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 1000000000 dollars");
}

TEST(ParagraphTest, BigQuantity) 
{
	CParagraph paragraph;
	string source = "I have one million three hundred thousand seventy nine dollars";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 1300079 dollars");
}

TEST(ParagraphTest, TextWithAllCombinations) 
{
	CParagraph paragraph;
	string source = "I have five hundred thousand dollars in my account, so I want to buy two cars, eleven bikes and donate ten thousand five hundred and one dollars";
    paragraph.TraverseParagraph(source);

    EXPECT_EQ (source, "I have 500000 dollars in my account, so I want to buy 2 cars, 11 bikes and donate 10501 dollars");
}




