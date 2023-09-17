#pragma once
#include "thpe04.h"
#include "..//catch.hpp"

//Class tests
TEST_CASE("stack class <int> - instantiate, insert, remove, topCard")
{
	stacky<int> data;
	data.insert(3);
	data.insert(6);
	CHECK(data.topCard() == 6);
	data.remove();
	CHECK(data.topCard() == 3);
}
TEST_CASE("stack class <card> - instantiate, insert, remove, topCard")
{
	stacky<card> data;
	card card1;
	card card2;
	card1.faceValue = 3;
	card1.suit = 2;
	card2.faceValue = 7;
	card2.suit = 1;
	data.insert(card1);
	data.insert(card2);
	CHECK(data.topCard().faceValue == 7);
	data.remove();
	CHECK(data.topCard().faceValue == 3);
}
TEST_CASE("stack class <int> - size()")
{
	stacky<int> data;
	CHECK(data.size() == 0);
	data.insert(3);
	data.insert(6);
	CHECK(data.size() == 2);
	data.remove();
	CHECK(data.size() == 1);
}
//getCardsRandom Tests
TEST_CASE("getCardsRandom - Correct Size")
{
	queue<card> player;
	getCardsRandom(player, 55);
	CHECK(player.size() == 52);
}

//== operator
TEST_CASE("==, should be true")
{
	card card1;
	card card2;
	card1.faceValue = 3;
	card1.suit = 2;
	card2.faceValue = 3;
	card2.suit = 2;
	CHECK(card1 == card2);
}

TEST_CASE("==, should be false")
{
	card card1;
	card card2;
	card1.faceValue = 3;
	card1.suit = 2;
	card2.faceValue = 7;
	card2.suit = 4;
	CHECK(!(card1 == card2));
}
//<< test cases
TEST_CASE("<< operator - Card Queue")
{
	ostringstream sout1;
	queue<card> data;
	card card1;
	card card2;
	card1.faceValue = 3;
	card1.suit = 2;
	card2.faceValue = 7;
	card2.suit = 1;
	data.push(card1);
	data.push(card2);
	sout1 << data;
	CHECK(sout1.str() == "3C 7D ");
}

TEST_CASE("<< operator - Card")
{
	ostringstream sout1, sout2;
	card card1;
	card card2;
	card1.faceValue = 3;
	card1.suit = 2;
	card2.faceValue = 7;
	card2.suit = 1;
	sout1 << card1;
	sout2 << card2;
	CHECK(sout1.str() == "3C");
	CHECK(sout2.str() == "7D");
}
//Play round test cases
TEST_CASE("playRound - one round win")
{
	ostringstream sout1, sout2;
	card card1;
	card card2;
	queue<card> player1;
	queue<card> player2;
	card1.faceValue = 3;
	card1.suit = 2;
	card2.faceValue = 7;
	card2.suit = 1;
	player1.push(card1);
	player2.push(card2);
	playRound(player1, player2);
	sout1 << player1;
	sout2 << player2;
	CHECK(sout2.str() == "3C 7D ");
	CHECK(sout1.str() == "");
}

TEST_CASE("playRound - Ties on cards")
{
	ostringstream sout1, sout2;
	card card1;
	card card2;
	card card3;
	card card4;
	queue<card> player1;
	queue<card> player2;
	card1.faceValue = 3;
	card1.suit = 2;
	card2.faceValue = 3;
	card2.suit = 2;
	card3.faceValue = 7;
	card3.suit = 2;
	card4.faceValue = 1;
	card4.suit = 2;
	player1.push(card1);
	player2.push(card2);
	player1.push(card3);
	player2.push(card4);
	playRound(player1, player2);
	sout1 << player1;
	sout2 << player2;
	CHECK(sout2.str() == "");
	CHECK(sout1.str() == "1C 3C 7C 3C ");
}