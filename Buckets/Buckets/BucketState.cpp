#include "BucketState.h"
#include <iostream>
#include <cassert>

int bucket_capicity[BUCKETS_COUNT] = { 8,5,3 };
int bucket_init_state[BUCKETS_COUNT] = { 8,0,0 };
int bucket_final_state[BUCKETS_COUNT] = { 4,4,0 };

BucketState::BucketState()
{
    SetBuckets(bucket_init_state);
    SetAction(8, -1, 0);
}

BucketState::BucketState(const int* buckets)
{
    SetBuckets(buckets);
    SetAction(8, -1, 0);
}

BucketState::BucketState(const BucketState& state)
{
    SetBuckets((const int*)state.bucket_s);
    SetAction(8, -1, 0);
}

BucketState& BucketState::operator=(const BucketState& state)
{
    SetBuckets((const int*)state.bucket_s);
    SetAction(state.curAction.water, state.curAction.from, state.curAction.to);

    return *this;
}

bool BucketState::IsSameState(const BucketState& state) const
{
    for (int i = 0; i < BUCKETS_COUNT; i++)
    {
        if (bucket_s[i] != state.bucket_s[i])
            return false;
    }
    return true;
}

//bool BucketState::operator==(const BucketState& state)
//{
//    return IsSameState(state);
//}

void BucketState::SetAction(int w, int f, int t)
{
    curAction.water = w;
    curAction.from = f;
    curAction.to = t;
}

void BucketState::SetBuckets(const int* buckets)
{
    for (int i = 0; i < BUCKETS_COUNT; i++)
    {
        this->bucket_s[i] = buckets[i];
    }
}

bool BucketState::CanTakeDumpAction(int from, int to)
{
    assert((from >= 0) && from < BUCKETS_COUNT);
    assert((to >= 0) && to < BUCKETS_COUNT);

    if ((from != to) && !IsBucketEmpty(from) && !IsBucketFull(to))
    {
        return true;
    }

    return false;
}

bool BucketState::IsBucketEmpty(int bucket)
{
    assert((bucket >= 0) && (bucket < BUCKETS_COUNT));

    return this->bucket_s[bucket] == 0;
}

bool BucketState::IsBucketFull(int bucket)
{
    assert((bucket >= 0) && (bucket < BUCKETS_COUNT));
    
    return this->bucket_s[bucket] == bucket_capicity[bucket];
}

void BucketState::PrintStates()
{
    std::cout << "Dump " << curAction.water << " water from " << curAction.from + 1 << " to " << curAction.to + 1 << ", ";
    std::cout << "buckets water states is : ";
    for (int i = 0; i < BUCKETS_COUNT; i++)
    {
        std::cout << bucket_s[i] << " ";
    }
    std::cout << std::endl;
}

bool BucketState::IsFinalState()
{
    return IsSameState(bucket_final_state);
}

/// <summary>
/// ��ǰ״ִ̬�й���֮�󣬸�ֵ��next��״̬
/// </summary>
/// <param name="from"></param>
/// <param name="to"></param>
/// <param name="next"></param>
/// <returns></returns>
bool BucketState::DumpWater(int from, int to, BucketState& next)
{
    next.SetBuckets(this->bucket_s);
    // to��Ͱ���ж���ʣ��ռ�
    int dumpWater = bucket_capicity[to] - this->bucket_s[to];

    // from��ˮ���ֱ࣬�ӵ�
    if (next.bucket_s[from] < dumpWater)
    {
        // û����ô��ˮ��
        dumpWater = next.bucket_s[from];
    }

    next.bucket_s[from] -= dumpWater;
    next.bucket_s[to] += dumpWater;

    if (dumpWater > 0)
    {
        // ��Ч�ĵ�ˮ����
        next.SetAction(dumpWater, from, to);
        return true;
    }

    return false;
}
