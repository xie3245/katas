#ifndef BOWLING_GAME_H
#define BOWLING_GAME_H

#include <cstdint>

class Game final
{
public:
	enum class State: uint8_t
	{
		none,
		spare,
		strike
	};

	Game(uint16_t initial_score = 0, State initial_state = State::none, uint8_t start_frame = 1) noexcept;

	void roll(const uint8_t pins_knocked) noexcept;
	uint16_t score() const noexcept;
	inline bool was_strike() const noexcept {
		return m_frame.m_prev_state == State::strike;
	}

	inline bool was_spare() const noexcept {
		return m_frame.m_prev_state == State::spare;
	}

private:
	bool is_bonus() const noexcept;
	struct Frame final
	{
		Frame(State initial_state, uint8_t start_frame) noexcept;
		void update(const uint8_t pins_knocked) noexcept;
		bool is_end() const noexcept;
		void next() noexcept;
		uint8_t m_frame_nr;
		uint8_t m_try;
		State m_prev_state;
		uint8_t m_pins_knocked;
	};

	Frame m_frame;

	uint16_t m_score;
};

#endif