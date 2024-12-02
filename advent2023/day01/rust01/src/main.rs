use std::{fs, usize};

fn main() {
    let contents = read_lines("input.txt");
    let mut values = 0;
    let numbers = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
    for line in contents{
        let mut calibration: (u32, u32) = (0, 0);
        for ch in 0..line.len() {
            for number in 0..numbers.len() as u32 {
                if line.len() < ch + numbers[number as usize].len() {continue;}
                if line[ch .. numbers[number as usize].len() + ch] == *numbers[number as usize] {
                    if calibration.0 == 0 {
                        calibration.0 = number;
                    }
                    calibration.1 = number;
                }
            }
            if calibration.0 == 0{
                calibration.0 = match line.chars().nth(ch) {
                    None => 0,
                    Some(ch) => match ch.to_digit(10){
                        None => 0,
                        Some(num) => num
                    }
                };
            }
            calibration.1 = match line.chars().nth(ch) {
                None => calibration.1,
                Some(ch) => match ch.to_digit(10){
                    None => calibration.1,
                    Some(num) => num
                }
            };
        }
        values += (calibration.0 * 10) + calibration.1;
    }

    println!("Total calibration values: {values}");
}

fn read_lines(filename: &str) -> Vec<String> {
    fs::read_to_string(filename)
        .unwrap()
        .lines()
        .map(String::from)
        .collect()
}
