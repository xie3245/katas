#include <catch2/catch.hpp>
#include "game.h"

TEST_CASE("simple score without bonuses")
{
	SECTION("roll 5, score 5")
	{
		Game bowling{};
		bowling.roll(5);
		REQUIRE(bowling.score() == 5);
	}

	SECTION("previous frame score 5, roll 2, 3, score 10")
	{
		Game bowling{5};
		bowling.roll(2);
		bowling.roll(3);
		REQUIRE(bowling.score() == 10);
	}
}

TEST_CASE("score with bonuses")
{
	SECTION("spare, roll 3, roll 5")
	{
		Game bowling{5, Game::State::spare};
		bowling.roll(3);
		REQUIRE(bowling.score() == 11);
		bowling.roll(5);
		REQUIRE(bowling.score() == 16);
	}

	SECTION("strike, roll 3, roll 5, roll 3")
	{
		Game bowling{15, Game::State::strike};
		bowling.roll(3);
		bowling.roll(5);
		REQUIRE(bowling.score() == 31);
		bowling.roll(3);
		REQUIRE(bowling.score() == 34);
	}
}

TEST_CASE("reach strike state")
{
	SECTION("previous none, then strike")
	{
		Game bowling{};
		bowling.roll(10);
		REQUIRE(bowling.was_strike());
		bowling.roll(2);
		bowling.roll(3);
		REQUIRE(bowling.score() == 20);
	}

	SECTION("roll 10 on second try, not strike")
	{
		Game bowling{};
		bowling.roll(0);
		bowling.roll(10);
		REQUIRE_FALSE(bowling.was_strike());
	}
}

TEST_CASE("reach spare state")
{
	SECTION("previous none, then spare")
	{
		Game bowling{};
		bowling.roll(2);
		bowling.roll(8);
		REQUIRE(bowling.was_spare());
		bowling.roll(2);
		REQUIRE(bowling.score() == 14);
	}
}

TEST_CASE("spare in 10th frame")
{
	SECTION("previous strike, then spare")
	{
		Game bowling{107, Game::State::strike, 10};
		bowling.roll(2);
		bowling.roll(8);
		REQUIRE(bowling.was_spare());
		bowling.roll(6);
		REQUIRE(bowling.score() == 133);
	}

	SECTION("previous none, then strike")
	{
		Game bowling{107, Game::State::none, 10};
		bowling.roll(10);
		REQUIRE(bowling.was_strike());
		bowling.roll(5);
		bowling.roll(2);
		REQUIRE(bowling.score() == 124);
	}

	SECTION("no more than 3 rolls")
	{
		Game bowling{107, Game::State::none, 10};
		bowling.roll(10);
		REQUIRE(bowling.was_strike());
		bowling.roll(5);
		bowling.roll(2);
		REQUIRE(bowling.score() == 124);
		bowling.roll(10);
		REQUIRE(bowling.score() == 124);
		bowling.roll(5);
		REQUIRE(bowling.score() == 124);
	}
}

TEST_CASE("example game")
{
	Game bowling{};
	bowling.roll(1);
	bowling.roll(4);
	bowling.roll(4);
	bowling.roll(5);
	bowling.roll(6);
	bowling.roll(4);
	bowling.roll(5);
	bowling.roll(5);
	bowling.roll(10);
	bowling.roll(0);
	bowling.roll(1);
	bowling.roll(7);
	bowling.roll(3);
	bowling.roll(6);
	bowling.roll(4);
	bowling.roll(10);
	bowling.roll(2);
	bowling.roll(8);
	bowling.roll(6);
	REQUIRE(bowling.score() == 133);
}