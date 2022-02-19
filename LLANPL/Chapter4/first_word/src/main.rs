fn main() {
    
    let s = String::from("hello, world");

    let hello = first_word(&s[..]);
    println!("The value of hello is: {}", hello);

    let s = "hello, world";

    let hello = first_word(s);
    println!("The value of hello is: {}", hello);
}

fn first_word(some_str: &str) -> &str {
    let as_bytes = some_str.as_bytes();

    for (i, &item) in as_bytes.iter().enumerate() {
        if item == b' '{
            return &some_str[..i];
        }
    }
    &some_str[..]
}
