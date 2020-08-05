#include "game.h"
#include<iostream>
#include <spdlog/spdlog.h>

namespace {
constexpr uint8_t extra_rolls_frame_nr = 11;
constexpr uint8_t max_num_pins = 10;
}

Game::Game(uint16_t initial_score, State initial_state, uint8_t start_frame) noexcept:
m_frame(initial_state, start_frame), m_score(initial_score)
{

}

void Game::roll(const uint8_t pins_knocked) noexcept
{
	if (m_frame.m_frame_nr > extra_rolls_frame_nr)
	{
		return;
	}

	auto is_normal_roll = [&]()->bool { return m_frame.m_frame_nr != extra_rolls_frame_nr; };

	if (is_normal_roll())
	{
		m_score += pins_knocked;
	}

	m_frame.update(pins_knocked);

	if (is_bonus())
	{
		m_score += pins_knocked;
	}

	if (m_frame.is_end())
	{
		m_frame.next();
	}
}

uint16_t Game::score() const noexcept
{
	return m_score;
}

bool Game::is_bonus() const noexcept
{
	const bool is_spare_bonus = was_spare() && m_frame.m_try == 1u;
	const bool is_strike_bonus = was_strike() && m_frame.m_try <= 2u;
	return is_spare_bonus || is_strike_bonus;
}

Game::Frame::Frame(State initial_state, uint8_t start_frame) noexcept:
m_frame_nr(start_frame), m_try(0u), m_prev_state(initial_state), m_pins_knocked(0u)
{

}

void Game::Frame::update(const uint8_t pins_knocked) noexcept
{
	++m_try;
	m_pins_knocked += pins_knocked;
	spdlog::debug("try: {}, pins: {}, frame: {}", m_try, m_pins_knocked, m_frame_nr);
}

bool Game::Frame::is_end() const noexcept
{
	return m_try >= 2u || m_pins_knocked == max_num_pins;
}

void Game::Frame::next() noexcept
{
	m_prev_state = State::none;
	if (m_try == 1u && m_pins_knocked == max_num_pins)
	{
		m_prev_state = State::strike;
	}

	if (m_try == 2u && m_pins_knocked == max_num_pins)
	{
		m_prev_state = State::spare;
	}

	++m_frame_nr;
	
	m_try = 0u;
	m_pins_knocked = 0u;
}
