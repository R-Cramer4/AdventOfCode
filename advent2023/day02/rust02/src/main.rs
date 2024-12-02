use std::fs;

fn main() {
    let lines = read_lines("input.txt");
    let mut ids = 0;
    let mut power_sum = 0;
    lines.iter().for_each(|line| {
        let mut line = line.split(":");
        let game_str = line.next().unwrap();
        let game_id = game_str.split(" ").last().unwrap().parse::<u32>().unwrap();
        let rounds = line.next().unwrap();
        let rounds = rounds.split(";").collect::<Vec<&str>>();

        let mut round_valid = true;
        let mut min_colors =  (0u32, 0u32, 0u32);
        rounds.iter().for_each(|round|{
            let cubes = round.split(",").collect::<Vec<&str>>();

            cubes.iter().for_each(|cube|{
                let cube = cube.trim().split(" ").collect::<Vec<&str>>();
                let cube_color = cube[1];
                let cube_count = cube[0].parse::<u32>().unwrap();

                match cube_color {
                    "red" => {
                        if cube_count > 12 {
                            round_valid = false;
                        }
                        if cube_count > min_colors.0 {
                            min_colors.0 = cube_count;
                        }
                    }
                    "green" => {
                        if cube_count > 13 {
                            round_valid = false;
                        }
                        if cube_count > min_colors.1 {
                            min_colors.1 = cube_count;
                        }
                    }
                    "blue" => {
                        if cube_count > 14 {
                            round_valid = false;
                        }
                        if cube_count > min_colors.2 {
                            min_colors.2 = cube_count
                        }
                    }
                    _ => {}
                }
            });
        });
        if round_valid {
            ids += game_id;
        }
        power_sum += min_colors.0 * min_colors.1 * min_colors.2;
    });

    println!("Valid game ids = {}", ids);
    println!("Total power sum = {}", power_sum);

}

fn read_lines(filename: &str) -> Vec<String> {
    fs::read_to_string(filename)
        .unwrap()
        .lines()
        .map(String::from)
        .collect()
}
