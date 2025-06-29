const std = @import("std");
const io = std.io;
const File = std.fs.File;

pub fn main() !void {
    const file = @embedFile("./day1.txt");
    var floor: i32 = 0;
    var pos: i32 = 0;
    for (file) |c| {
        pos += 1;
        // std.debug.print("{c}\n", .{c});
        if (c == '(') {
            floor += 1;
        } else {
            floor -= 1;
        }
        if (floor == -1) {
            std.debug.print("position: {d}\n", .{pos});
        }
    }

    std.debug.print("floor: {d}\n", .{floor});
}
