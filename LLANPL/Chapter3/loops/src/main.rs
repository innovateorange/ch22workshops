fn main() {
    let mut counter = 0;
    let result = loop {
        counter += 1;

        if counter == 10{
            break counter * 2;
        }
    };

    println!("The value of result is: {}", result);
}