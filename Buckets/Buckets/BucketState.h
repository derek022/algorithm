#pragma once

#define BUCKETS_COUNT 3

typedef struct tagAction
{
    int from;
    int to;
    int water;
}Action;

struct BucketState
{
    BucketState();
    BucketState(const int* buckets);
    BucketState(const BucketState& state);
    BucketState& operator = (const BucketState & state);
    bool IsSameState(const BucketState& state)const;
    //bool operator==(const BucketState& state);

    void SetAction(int w, int f, int t);
    void SetBuckets(const int* buckets);
    
    bool CanTakeDumpAction(int from, int to);
    bool IsBucketEmpty(int bucket);
    bool IsBucketFull(int bucket);
    void PrintStates();
    bool IsFinalState();
    bool DumpWater(int from, int to, BucketState& next);

    int bucket_s[BUCKETS_COUNT];
    Action curAction;
};