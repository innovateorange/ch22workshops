use std::io;




fn main() {
    println!("Computer the n'th fibonacci number!");
    println!("Enter n: ");

    let mut n = String::new();

    io::stdin()
    .read_line(&mut n)
    .expect("Not a valid input");

    let n: u32 = match n.trim().parse() {
        Ok(num)=>num,
        Err(_)=> {
            println!("Not a valid input, setting n = 1");
            1
        }
    };

    let f:u32 = fibonacci(n);
    println!("The {}'th fibonacci number is: {}", n, f)    

}

fn fibonacci(n: u32) -> u32 {
    if n == 1 {
        1
    } else if n == 2 {
        1
    } else {
        fibonacci(n-1) + fibonacci(n - 2)
    }

}
