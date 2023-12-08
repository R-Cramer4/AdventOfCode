use std::fs;

fn main() {
    let contents = read_lines("input.txt");
    let mut values = 0;
    for line in contents{
        let size = line.chars();
        let mut calibration: (u32, u32) = (0, 0);
        for ch in size {
            if calibration.0 == 0{
                calibration.0 = match ch.to_digit(10){
                    None => 0,
                    Some(num) => num
                };
            }
            calibration.1 = match ch.to_digit(10){
                None => calibration.1,
                Some(num) => num
            }
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
