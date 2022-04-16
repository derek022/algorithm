// Buckets.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "BucketState.h"
#include <deque>
#include <functional>
#include <algorithm>
#include <cassert>

using namespace std;
static int resultCount = 0;

bool IsSameBucketState( BucketState& const state1, BucketState& const state2)
{
    return state1.IsSameState(state2);
}

/// <summary>
/// 剪枝和重复状态判断
/// </summary>
/// <param name="states">历史记录的状态</param>
/// <param name="newState">当前状态</param>
/// <returns>true:已经记录过，false:没有记录在案</returns>
bool IsProcessedState(std::deque<BucketState>& states, const BucketState& newState)
{
    std::deque<BucketState>::iterator it = states.end();

    it = find_if(states.begin(), states.end(), std::bind(std::ptr_fun(IsSameBucketState),std::placeholders::_1, newState));

    return it != states.end();
}

void PrintResult(std::deque<BucketState>& states)
{
    std::cout << "Find Result " << ++resultCount << ", total moves : " << states.size() << std::endl;
    for_each(states.begin(), states.end(), std::mem_fun_ref(&BucketState::PrintStates));

    std::cout << std::endl << std::endl;
}


void SearchState(std::deque<BucketState>& states);

/// <summary>
/// 递归搜索  判断执行倒水，剪枝，递归
/// </summary>
/// <param name="states"></param>
/// <param name="current"></param>
/// <param name="from"></param>
/// <param name="to"></param>
void SearchStateOnAction(std::deque<BucketState>& states, BucketState& current, int from, int to)
{
    if (current.CanTakeDumpAction(from, to))
    {
        BucketState next;
        bool bDump = current.DumpWater(from, to, next);
        if (bDump && !IsProcessedState(states, next))
        {
            states.push_back(next);
            SearchState(states);
            states.pop_back();
        }
    }
}

/// <summary>
/// 搜索函数
/// </summary>
/// <param name="states"></param>
void SearchState(std::deque<BucketState>& states)
{
    BucketState current = states.back();
    if (current.IsFinalState())
    {
        PrintResult(states);
        return;
    }


    for (int to = 0; to < BUCKETS_COUNT; to++)
    {
        for (int from = 0; from < BUCKETS_COUNT; from++)
        {
            SearchStateOnAction(states, current, from, to);
        }
    }
}

int main()
{
    std::cout << "Hello World!\n";
    
    std::deque<BucketState> states;
    BucketState init;
    states.push_back(init);
    SearchState(states);

    assert(states.size() == 1);

    return 0;
}
