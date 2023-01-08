ifidni MODEL,s
include "small.inc"
else
ifidni MODEL,m
include "medium.inc"
else
ifidni MODEL,l
include "large.inc"
else
error "Unsupported MODEL; assign 's', 'm' or 'l' to macro MODEL"
endif
endif
endif
