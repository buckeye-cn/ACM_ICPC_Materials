# https://open.kattis.com/problems/clockpictures

n = gets.to_i
x = gets.split.map(&:to_i).sort
y = gets.split.map(&:to_i).sort
x.push(x[0] + 360000)
y.push(y[0] + 360000)
x = x.each_cons(2).map{|a, b|(b - a).to_s}.join
y = y.each_cons(2).map{|a, b|(b - a).to_s}.join

if (x * 2).include?(y)
    puts('possible')
else
    puts('impossible')
end
