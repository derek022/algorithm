#include "TubesState.h"
#include <cassert>
#include <iostream>


int tube_capicity[TUBES_COUNT] = { 4,4,4,4,4 };
int tube_init_state[TUBES_COUNT][BALL_COUNT] = { {3,1,2,1},{1,3,2,2},{2,1,3,3},{0,0,0,0},{0,0,0,0} };


TubesState::TubesState()
{
	SetTubes(tube_init_state);
	SetAction(-1, -1, -1);
}

TubesState::TubesState(const int (*tubes)[4])
{
	SetTubes(tubes);
	SetAction(-1, -1, -1);
}

TubesState::TubesState(const TubesState& state)
{
	SetTubes(state.balls_s);
	SetAction(-1, -1, -1);
}

TubesState& TubesState::operator=(const TubesState& state)
{
	SetTubes(state.balls_s);
	SetAction(state.curAction.ball, state.curAction.from, state.curAction.to);

	return *this;
}

bool TubesState::IsSameState(const TubesState& state) const
{
	for (int i = 0; i < TUBES_COUNT; i++)
	{
		for (int j = 0; j < BALL_COUNT; j++)
		{
			if (balls_s[i][j] != state.balls_s[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

void TubesState::SetAction(int b, int f, int t)
{
	curAction.ball = b;
	curAction.from = f;
	curAction.to = t;
}

void TubesState::SetTubes(const int(*tubes)[4])
{
	for (int i = 0; i < TUBES_COUNT; i++)
	{
		for (int j = 0; j < BALL_COUNT; j++)
		{
			this->balls_s[i][j] = tubes[i][j];
		}
	}
}

bool TubesState::CanTakeDumpAction(int from, int to)
{

	assert((from >= 0) && from < TUBES_COUNT);
	assert((to >= 0) && to < TUBES_COUNT);

	if (IsTubeComplete(from) || IsTubeComplete(to))
	{
		return false;
	}

	if ((from != to) && !IsTubeEmpty(from) && !IsTubeFull(to) )
	{
		if (IsSameTop(from, to) || IsTubeEmpty(to))
		{
			return true;
		}
	}



	return false;
}

bool TubesState::IsTubeEmpty(int tube)
{
	assert((tube >= 0) && (tube < TUBES_COUNT));

	return this->balls_s[tube][0] == 0;
}

bool TubesState::IsTubeFull(int tube)
{
	assert((tube >= 0) && (tube < TUBES_COUNT));

	return this->balls_s[tube][BALL_COUNT  - 1] != 0;;
}

bool TubesState::IsSameTop(int f, int t)
{

	int fTop = GetTopBallValue(f);
	int tTop = GetTopBallValue(t);

	return fTop == tTop;
}

bool TubesState::IsTubeComplete(int tube)
{
	int bottomValue = this->balls_s[tube][0];
	for (int i = 1; i < BALL_COUNT; i++)
	{
		if (this->balls_s[tube][i] != bottomValue)
		{
			return false;
		}
	}
	return bottomValue != 0;
}

int TubesState::GetTopBallValue(int tube)
{
	assert((tube >= 0) && (tube < TUBES_COUNT));

	for (int i = BALL_COUNT - 1; i >= 0; i--)
	{
		if (this->balls_s[tube][i] != 0)
		{
			return this->balls_s[tube][i];
		}
	}
	return 0;
}

int TubesState::GetTopBallIndex(int tube)
{
	for (int i = BALL_COUNT - 1; i >= 0; i--)
	{
		if (this->balls_s[tube][i] != 0)
		{
			return i;
		}
	}
	return -1;
}

void TubesState::PrintStates()
{
	std::cout << "Dump " << curAction.ball << " ball from " << curAction.from + 1 << " to " << curAction.to + 1 << ", ";
	std::cout << "tube ball states is : " << std::endl;

	for (int j = BALL_COUNT - 1; j >=0 ; j--)
	{
		for (int i = 0; i < TUBES_COUNT; i++)
		{
			std::cout << balls_s[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;
}


bool TubesState::IsFinalState()
{
	for (int i = 0; i < TUBES_COUNT; i++)
	{
		int bottomBall = this->balls_s[i][0];
		for (int j = 1; j < BALL_COUNT; j++)
		{
			if (bottomBall != this->balls_s[i][j])
			{
				return false;
			}
		}
	}
	return true;
}



bool TubesState::DumpBall(int from, int to, TubesState& next)
{
	next.SetTubes(this->balls_s);
	int balls = next.GetSameBalls(from);
	int emptySize = next.GetEmptySize(to);
	int ballValue = next.GetTopBallValue(from);

	int fromTop = next.GetTopBallIndex(from);
	int toTop = next.GetTopBallIndex(to);

	if (balls > emptySize)
	{
		balls = emptySize;
	}

	for (int i = 0; i < balls; i++)
	{
		next.balls_s[from][fromTop - i] = 0;
		next.balls_s[to][toTop + i + 1] = ballValue;
	}

	if (balls > 0)
	{
		next.SetAction(balls, from, to);
		return true;
	}

	return false;
}

int TubesState::GetSameBalls(int tube)
{
	int topBallIndex = 0;
	int balls = 1;
	for (int i = BALL_COUNT - 1; i >= 0; i--)
	{
		if (this->balls_s[tube][i] != 0)
		{
			topBallIndex = i;
			//break;
		}
	}
	
	for (int i = topBallIndex - 1; i >= 0; i--)
	{
		if (this->balls_s[tube][i] == topBallIndex)
		{
			balls++;
		}
	}

	return balls;
}

int TubesState::GetEmptySize(int tube)
{
	int size = 0;
	for (int i = BALL_COUNT - 1; i >= 0; i--)
	{
		if (this->balls_s[tube][i] == 0)
		{
			size++;
		}
		else
		{
			break;
		}
	}
	return size;
}
