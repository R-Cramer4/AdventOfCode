use std::{collections::{BinaryHeap, HashMap}, fs};


fn main() {
    let mut distances = 0;
    let mut similarity = 0;
    let contents = read_lines("input.txt");
    let mut left = BinaryHeap::new();
    let mut right = BinaryHeap::new();
    let mut right_map = HashMap::new();
    for line in contents{
        let mut parts = line.split_whitespace();
        let l = parts.next().expect("none").parse::<i32>().unwrap();
        let r = parts.next().expect("none").parse::<i32>().unwrap();
        left.push(l);
        right.push(r);
        right_map.entry(r).and_modify(|r| *r += 1).or_insert(1);
    }
    while !left.is_empty() {
        distances += (left.peek().unwrap() - right.peek().unwrap()).abs();
        similarity += left.peek().unwrap() *(match right_map.get(left.peek().unwrap()){
            Some(i) => &i,
            None => &0,
        });
        left.pop();
        right.pop();
    }
    println!("Distances: {distances}");
    println!("Similarity: {similarity}");
}
fn read_lines(filename: &str) -> Vec<String> {
    fs::read_to_string(filename)
        .unwrap()
        .lines()
        .map(String::from)
        .collect()
}
