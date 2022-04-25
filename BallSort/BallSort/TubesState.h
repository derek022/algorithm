#pragma once

#define TUBES_COUNT 5
#define BALL_COUNT 4

typedef struct tabAction
{
	int from;
	int to;
	int ball;
}Action;

struct TubesState
{
	TubesState();
	TubesState(const int(*tubes)[4]);
	TubesState(const TubesState& state);
	TubesState& operator = (const TubesState& state);
	bool IsSameState(const TubesState& state)const;

	void SetAction(int b, int f, int t);
	void SetTubes(const int(*tubes)[4]);

	bool CanTakeDumpAction(int from, int to);
	bool IsTubeEmpty(int tube);
	bool IsTubeFull(int tube);
	bool IsSameTop(int f, int t);
	bool IsTubeComplete(int tube);
	bool IsAllSameBall(int tube);
	int GetTopBallValue(int tube);
	int GetTopBallIndex(int tube);
	void PrintStates();
	bool IsFinalState();
	bool DumpBall(int from, int to, TubesState& next);

	int GetSameBalls(int tube);
	int GetEmptySize(int tube);

	int balls_s[TUBES_COUNT][BALL_COUNT];
	Action curAction;
};

