# Cache Replacement Policy: FIFO vs Second Chance

A C project that compares two cache replacement policies, FIFO and Second Chance (Clock), on a fixed-size cache. We wanted to see how much a simple reference bit can reduce cache pollution and thrashing compared with plain FIFO.

Group project, Department of CSE, East West University.

## Why this project
A cache can only hold a few items. When it is full, the replacement policy decides which item to remove. FIFO always removes the oldest item, even if it is still being used. This can throw away useful pages and cause extra misses.

Second Chance fixes part of this. Every slot has a reference bit, and a page that was used recently gets one more chance before it is removed.

## How the two policies work

**FIFO**
- A `front` pointer always points to the oldest page.
- On a miss, the page at `front` is replaced and the pointer moves forward.
- On a hit, nothing changes.

**Second Chance (Clock)**
- Each slot has a `refBit`, and a `hand` pointer moves around the cache in a circle.
- On a hit, the page's `refBit` is set to 1.
- On a miss, the hand skips pages with `refBit = 1` (and resets them to 0) and replaces the first page with `refBit = 0`.

## Test setup
- Cache size: 4
- Page sequence: `1 2 3 4 5 2 6 2 7 2 8 2`
- Both programs use the same cache size and the same sequence.

## Results

| Policy | Hits | Misses | Hit ratio |
|--------|------|--------|-----------|
| FIFO | 3 | 9 | 25.00% |
| Second Chance | 4 | 8 | 33.33% |

Page 2 is used again and again in this sequence. FIFO removes it when it becomes the oldest page, so it misses on it later. Second Chance keeps it because its reference bit gets set on every hit.

This is only a small test with 12 requests, so it shows the idea but does not prove Second Chance is always better.

## Files
| File | What it is |
|------|------------|
| `fifo_cache.c` | FIFO implementation |
| `second_chance_cache.c` | Second Chance implementation |
| `presentation.pdf` | Our project slides |

## Run it
```bash
gcc fifo_cache.c -o fifo
./fifo

gcc second_chance_cache.c -o second_chance
./second_chance
```

## What we want to try next
- Segmented LRU (SLRU)
- LFU with aging
- Adaptive Replacement Cache (ARC)
- Multiple reference bits or access counters
- Larger tests, such as web cache or database access traces

## Team
- Sadia Afrin Suchi
- Md Abdus Salam Fahad
- Sadia Khan Farhin
- Nasheba Afrin Ruba

Supervised by Dr. Md. Nawab Yousuf Ali, Professor, Department of CSE, East West University.

**My part (Nasheba Afrin Ruba):** I worked on the Second Chance implementation in C, ran both programs on the same page sequence to compare hits, misses and hit ratio, and helped prepare the presentation slides.
