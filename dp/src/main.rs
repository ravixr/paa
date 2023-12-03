use std::time::Instant;
use rand::Rng;


fn knapsack01_greedy(items: Vec<(usize, usize)>, capacity: usize) -> usize {
    let mut items = items;
    items.sort_by(|a, b| (b.1 / b.0).cmp(&(a.1 / a.0)));
    let mut capacity = capacity;
    let mut res = 0;
    for item in items {
        if capacity >= item.0 {
            res += item.1;
            capacity -= item.0;
        }
    }
    res
}

fn knapsack01_dp(items: Vec<(usize, usize)>, capacity: usize) -> usize {
    let mut memo = vec![0; capacity + 1];
    for i in 1..=items.len() {
        for j in (1..=capacity).rev() {
            if j >= items[i - 1].0 {
                memo[j] = memo[j].max(memo[j - items[i - 1].0] + items[i - 1].1);
            }
        }
    }
    memo[capacity]
}

fn generate_random_items(n: usize, max_weight: usize, max_value: usize) -> Vec<(usize, usize)> {
    let mut rng = rand::thread_rng();
    let mut items = vec![];
    for _ in 0..n {
        let weight = rng.gen_range(1..=max_weight);
        let value = rng.gen_range(1..=max_value);
        items.push((weight, value));
    }
    items
}

fn main() {
    let n = [ 100, 1000, 10000, 100000 ];
    println!("n, greedy_time, greedy_res, dp_time, dp_res");
    for i in 0..n.len() {
        for _ in 0..3 {
            let items = generate_random_items(n[i], 100, 100);
            let capacity = 1000;
            let start1 = Instant::now();
            let res1 = knapsack01_greedy(items.clone(), capacity);
            let end1 = Instant::now();
            let start2 = Instant::now();
            let res2 = knapsack01_dp(items.clone(), capacity);
            let end2 = Instant::now();
            println!("{}, {}, {}, {}, {}", n[i], (end1 - start1).as_nanos(), res1, (end2 - start2).as_nanos(), res2);
        }
    }
}