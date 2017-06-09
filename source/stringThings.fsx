let str = """
    { 'a', ".-" },
    { 'b', "-..." },
	{ 'c', "-.-." },
	{ 'd', "-.." },
	{ 'e', "." },
	{ 'f', "..-." },
	{ 'g', "--." },
	{ 'h', "...." },
	{ 'i', ".." },
	{ 'j', ".---" },
	{ 'k', "-.-" },
	{ 'l', ".-.." },
	{ 'm', "--" },
	{ 'n', "-." },
	{ 'o', "---" },
	{ 'p', ".--." },
	{ 'q', "--.-" },
	{ 'r', ".-." },
	{ 's', "..." },
	{ 't', "-" },
	{ 'u', "..-" },
	{ 'v', "...-" },
	{ 'w', ".--" },
	{ 'x', "-..-" },
	{ 'y', "-.--" },
	{ 'z', "--.." },
"""

open System.Text.RegularExpressions

let chopUp x = 
    let r = @"[-.]+"
    let m = Regex.Matches( x, r)
    m |> Seq.cast |> Seq.map (fun (x:Match) -> x.Value)

{'a'..'z'} 
{'0'..'9'}

let formatIt (x:string, y:char) =
    let spaces = String.replicate (10 - x.Length) " "
    "\"" + x + "\"," + spaces + "// " + y.ToString()
    

Seq.zip (chopUp str) {'a'..'z'} |> Seq.map (fun (x, y) -> formatIt (x, y) ) |> Seq.iter (fun x -> printfn "%s" x)

let num = """
	{ '0', "-----" },
	{ '1', ".----" },
	{ '2', "..---" },
	{ '3', "...--" },
	{ '4', "....-" },
	{ '5', "....." },
	{ '6', "-...." },
	{ '7', "--..." },
	{ '8', "---.." },
	{ '9', "----." },
"""

let sym = """
	{ '.', ".-.-.-" },
	{ ',', "--..--" },
	{ ':', "---..." },
	{ '?', "..--.." }, 
	{ '-', "-....-" },
	{ '/', "-..-." },
	{ '(', "-.--." },
	{ ')', "-.--.-" },
	{ '"', ".-..-." },
	{ '=', "-...-" },
    { '%', "...-." },
	{ '+', ".-.-." },
    { '}', ".-..." }, 
    { '>', "...-.-" },
    { '<', "-.-.-" }, 
	{ '@', ".--.-." },
"""



Seq.zip (chopUp num) {'0'..'9'} |> Seq.map (fun (x, y) -> formatIt (x, y) ) |> Seq.iter (fun x -> printfn "%s" x)
chopUp sym

let one = 
    let r = @"\'\S\'"
    Regex.Matches( sym, r)
    |> Seq.cast 
    |> Seq.map (fun (x:Match) -> x.Value) 
    // |> Seq.iter (fun x -> printfn "%s" x)

let two = 
    let r = "\"[-.]+\""
    Regex.Matches( sym, r)
    |> Seq.cast 
    |> Seq.map (fun (x:Match) -> x.Value) 
    // |> Seq.iter (fun x -> printfn "%s" x)

let fIt (x:string, y:string) =
    "else if (c == " + y  + ") signalCode(" + x + ");"
    

Seq.zip two one |> Seq.iter (fun (x,y) -> printfn "%s" (fIt (x,y) ) ) 

"""
else if (c == ' ') signalCode(" ");
"""
