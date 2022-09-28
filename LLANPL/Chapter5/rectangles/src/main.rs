// fn main() {
//     let width1 = 30;
//     let height1 = 50;

//     println!("The area of the rectange is {} square pixels", 
//     area(width1, height1));

// }

// fn area(w: u32, h: u32) -> u32 {
//     w * h
// }

// fn main() {
//     let rect1 = (30, 50);

//     println!("The area of the rectangle is {} square pixels", 
//     area(rect1));
// }

// fn area( dimensions: (u32, u32))-> u32 {
//     dimensions.0 * dimensions.1
// }
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}
impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }
    fn can_hold(&self, rect2: &Rectangle) -> bool{
        if self.width > rect2.width && self.height > rect2.height{
            true
        }else{
            false
        }
        
    }

    fn square(size: u32) -> Rectangle {
        Rectangle {
            width: size,
            height: size
        }
    }
}


fn main() {
    let rect1 = Rectangle {
        width: 30,
        height: 50,
    };

    let rect2 = Rectangle {
        width: 10,
        height: 40,
    };
    let rect3 = Rectangle {
        width: 60,
        height: 45,
    };
    println!("The area of rect1 is {} sq pixels", rect1.area());

    println!("Can rect1 hold rect2? {}", rect1.can_hold(&rect2));
    println!("Can rect1 hold rect3? {}", rect1.can_hold(&rect3));

}


