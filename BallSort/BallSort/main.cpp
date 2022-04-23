// BallSort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "TubesState.h"
#include <deque>
#include <functional>
#include <algorithm>
#include <cassert>
using namespace std;
static int resultCount = 0;


bool IsSameTubeState(const TubesState&  state1, const TubesState&  state2)
{
    return state1.IsSameState(state2);
}

/// <summary>
/// 剪枝和重复状态判断
/// </summary>
/// <param name="states">历史记录的状态</param>
/// <param name="newState">当前状态</param>
/// <returns>true:已经记录过，false:没有记录在案</returns>
bool IsProcessedState(std::deque<TubesState>& states, const TubesState& newState)
{
    std::deque<TubesState>::iterator it = states.end();

    it = find_if(states.begin(), states.end(), std::bind(std::ptr_fun(IsSameTubeState), std::placeholders::_1, newState));

    return it != states.end();
}

void PrintResult(std::deque<TubesState>& states)
{
    std::cout << "Find Result " << ++resultCount << ", total moves : " << states.size() << std::endl;
    for_each(states.begin(), states.end(), std::mem_fun_ref(&TubesState::PrintStates));

    std::cout << std::endl << std::endl;
}


bool SearchState(std::deque<TubesState>& states);

/// <summary>
/// 递归搜索  判断执行倒水，剪枝，递归
/// </summary>
/// <param name="states"></param>
/// <param name="current"></param>
/// <param name="from"></param>
/// <param name="to"></param>
bool SearchStateOnAction(std::deque<TubesState>& states, TubesState& current, int from, int to)
{
    bool rst = false;
    if (current.CanTakeDumpAction(from, to))
    {
        TubesState next;
        bool bDump = current.DumpBall(from, to, next);
        if (bDump && !IsProcessedState(states, next))
        {
            states.push_back(next);
            rst = SearchState(states);
            states.pop_back();
        }
    }

    return rst;
}

/// <summary>
/// 搜索函数
/// </summary>
/// <param name="states"></param>
bool SearchState(std::deque<TubesState>& states)
{
    TubesState current = states.back();
    if (current.IsFinalState())
    {
        PrintResult(states);
        return true;
    }


    for (int to = 0; to < TUBES_COUNT; to++)
    {
        for (int from = 0; from < TUBES_COUNT; from++)
        {
            // 如果管子全都是一个颜色，则不需要往别的管子移动，
            
            if (SearchStateOnAction(states, current, from, to))
            {
                return true;
            }
        }
    }

    return false;
}


int main()
{
    std::cout << "Hello World!\n";
    std::deque<TubesState> states;
    TubesState init;
    states.push_back(init);
    SearchState(states);

    assert(states.size() == 1);

    return 0;
}

