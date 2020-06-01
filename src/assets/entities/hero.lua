Entity = {
   
   AnimatedComponent = {
      frame_time = 500,
      looped = true,
      n_frames = 2,
      frames = {
	 frame_1 = {
	    x = 0,
	    y = 0,
	    w = 64,
	    h = 64
	 },
	 frame_2 = {
	    x = 64,
	    y = 0,
	    w = 64,
	    h = 64
	 }
      }
   },

   MotionComponent = {
      dx = 0.1,
      dy = 0,
      ddx = 0.0003,
      ddy = 0
   },

   RenderComponent = {
      zIndex = 0,
      atlas_id = 0,
      frame = {
	 x = 0,
	 y = 0,
	 w = 64,
	 h = 64
      }
   },

   TransformComponent = {
      x = 100,
      y = 100,
      scale_x = 2,
      scale_y = 2,
      rotation = 0
   }

}
