
local ctx = require('exrc').init()
local overseer = require('overseer')



overseer.register_template{
  name = 'build_app',
  condition = {dir = ctx.exrc_dir},
  builder = function (params)
    return {
      name = "build",
      cwd = ctx.exrc_dir,
      cmd = 'lua lua_scripts/build.lua',
      components = { { "on_output_quickfix", open = true }, "default" },
    }
    
  end
}

overseer.register_template{
  name = 'run app',
  condition = {dir = ctx.exrc_dir},
  builder = function (params)
    return {
      name = "run",
      cwd = ctx.exrc_dir,
      cmd = 'lua lua_scripts/run.lua',
      components = { { "on_output_quickfix", open = true }, "default" },
    }
    
  end
}
overseer.register_template{
  name = 'reload compile_commands',
  condition = {dir = ctx.exrc_dir},
  builder = function (params)
    return {
      name = "reload_commands",
      cwd = ctx.exrc_dir,
      cmd = 'lua lua_scripts/reload_commands.lua',
      components = { { "on_output_quickfix", open = true }, "default" },
    }
    
  end
}
overseer.register_template{
  name = 'compile shaders',
  condition = {dir = ctx.exrc_dir},
  builder = function (params)
    return {
      name = "comp_shaders",
      cwd = ctx.exrc_dir,
      cmd = 'lua lua_scripts/compile_shaders.lua',
      components = { { "on_output_quickfix", open = true }, "default" },
    }
  end
}
