function WriteCompileCommands()
  local file = io.open("fragments", "r") -- Open the file in read mode
  local content = " "

  if file then
    content = file:read("*a") -- Read the entire file content
    content  = content:sub(1, -3)
    content = "[" .. content .. "]"
    file:close() -- Close the filename
  else
      print("Error opening fragments file.")
  end

  local output = io.open("compile_commands.json", "w+") -- overwrite
  if output then
      output:write(content)
      output:close()
  else
      print("Error opening compile_commands file.")
  end
end


WriteCompileCommands()
