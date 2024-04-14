pub mod word_gen {
    use std::fs::File;
    use std::io::{BufRead, BufReader};
    use rand::Rng;

    pub fn gen_word() -> String {
        // Apparently Rust closes the file when it goes out of scope. This is really just to test the syntax of this
        let line_count: usize = 
        {
            let f = File::open("words.txt").expect("Unable to open file\n");
            let reader: BufReader<File> = BufReader::new(f);
            reader.lines().count()
        };

        let word_index: usize = rand::thread_rng().gen_range(0..line_count);

        {
            let f = File::open("words.txt").expect("Unable to open file\n");
            let reader = BufReader::new(f);
            reader.lines().nth(word_index).unwrap().unwrap()
        }
    }
}