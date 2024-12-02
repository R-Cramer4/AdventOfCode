use std::fs;

fn main() {
    let lines = read_lines("input.txt");
    let mut sum_parts = 0;

    lines.iter().for_each(|line| {
        line.chars().for_each(|ch|{
            if !ch.is_digit(10) && ch != '.'{
                sum_parts += find_numbers(&lines, line, &ch);
            }
        });
    });

}

fn find_numbers(lines: &Vec<String>, line: &str, ch: &char) -> i32{


    0
}

fn read_lines(filename: &str) -> Vec<String> {
    fs::read_to_string(filename)
        .unwrap()
        .lines()
        .map(String::from)
        .collect()
}
