static const char canvas_htm[] PROGMEM = "<html>\n"\
"	<head>\n"\
"		<meta charset=\"utf-8\">\n"\
"		<meta name=\"viewport\" content=\"width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0\">\n"\
"		\n"\
"		<style>\n"\
"		body {\n"\
"			overflow	: hidden;\n"\
"			padding		: 0;\n"\
"			margin		: 0;\n"\
"			background-color: #001a33;\n"\
"			color: #ffffff;\n"\
"		}\n"\
"		\n"\
"		.button {\n"\
"		  width: 50%;\n"\
"		  background-color: Gray;\n"\
"		  margin: 6px 2px;\n"\
"		  border: none;\n"\
"		  color: white;\n"\
"		  padding: 10px 20px;\n"\
"		  text-align: center;\n"\
"		  text-decoration: none;\n"\
"		  display: inline-block;\n"\
"		  font-size: 16px;\n"\
"		}\n"\
"		\n"\
"		#info {\n"\
"			position	: absolute;\n"\
"			top		: 0px;\n"\
"			width		: 100%;\n"\
"			padding		: 5px;\n"\
"			text-align	: center;\n"\
"		}\n"\
"		#info a {\n"\
"			color		: #66F;\n"\
"			text-decoration	: none;\n"\
"		}\n"\
"		#info a:hover {\n"\
"			text-decoration	: underline;\n"\
"		}\n"\
"		#container {\n"\
"			width		: 100%;\n"\
"			height		: 100%;\n"\
"			overflow	: hidden;\n"\
"			padding		: 0;\n"\
"			margin		: 0;\n"\
"			-webkit-user-select	: none;\n"\
"			-moz-user-select	: none;\n"\
"		}\n"\
"        .rotate180 {\n"\
"            -webkit-transform: rotate(180deg);\n"\
"            -moz-transform: rotate(180deg);\n"\
"            -o-transform: rotate(180deg);\n"\
"            -ms-transform: rotate(180deg);\n"\
"            transform: rotate(180deg);\n"\
"            width:100%;\n"\
"            height:100%;\n"\
"			object-fit: contain;\n"\
"			object-position: right bottom;\n"\
"        }\n"\
"		img {\n"\
"		  pointer-events: none;\n"\
"		}\n"\
"		</style>\n"\
"	</head>\n"\
"	<body scroll=\"no\">\n"\
"		<script>\n"\
"		var VirtualJoystick	= function(opts)\n"\
"{\n"\
"	opts			= opts			|| {};\n"\
"	this._container		= opts.container	|| document.body;\n"\
"	this._strokeStyle	= opts.strokeStyle	|| 'GRAY';\n"\
"	this._stickEl		= opts.stickElement	|| this._buildJoystickStick();\n"\
"	this._baseEl		= opts.baseElement	|| this._buildJoystickBase();\n"\
"	this._mouseSupport	= opts.mouseSupport !== undefined ? opts.mouseSupport : false;\n"\
"	this._stationaryBase	= opts.stationaryBase || false;\n"\
"	this._baseX		= this._stickX = opts.baseX || 0\n"\
"	this._baseY		= this._stickY = opts.baseY || 0\n"\
"	this._limitStickTravel	= opts.limitStickTravel || false\n"\
"	this._stickRadius	= opts.stickRadius !== undefined ? opts.stickRadius : 100\n"\
"	this._useCssTransform	= opts.useCssTransform !== undefined ? opts.useCssTransform : false\n"\
"\n"\
"	this._container.style.position	= \"relative\"\n"\
"\n"\
"	this._container.appendChild(this._baseEl)\n"\
"	this._baseEl.style.position	= \"absolute\"\n"\
"	this._baseEl.style.display	= \"none\"\n"\
"	this._container.appendChild(this._stickEl)\n"\
"	this._stickEl.style.position	= \"absolute\"\n"\
"	this._stickEl.style.display	= \"none\"\n"\
"\n"\
"	this._pressed	= false;\n"\
"	this._touchIdx	= null;\n"\
"	\n"\
"	if(this._stationaryBase === true){\n"\
"		this._baseEl.style.display	= \"\";\n"\
"		this._baseEl.style.left		= (this._baseX - this._baseEl.width /2)+\"px\";\n"\
"		this._baseEl.style.top		= (this._baseY - this._baseEl.height/2)+\"px\";\n"\
"	}\n"\
"    \n"\
"	this._transform	= this._useCssTransform ? this._getTransformProperty() : false;\n"\
"	this._has3d	= this._check3D();\n"\
"	\n"\
"	var __bind	= function(fn, me){ return function(){ return fn.apply(me, arguments); }; };\n"\
"	this._$onTouchStart	= __bind(this._onTouchStart	, this);\n"\
"	this._$onTouchEnd	= __bind(this._onTouchEnd	, this);\n"\
"	this._$onTouchMove	= __bind(this._onTouchMove	, this);\n"\
"	this._container.addEventListener( 'touchstart'	, this._$onTouchStart	, false );\n"\
"	this._container.addEventListener( 'touchend'	, this._$onTouchEnd	, false );\n"\
"	this._container.addEventListener( 'touchmove'	, this._$onTouchMove	, false );\n"\
"	if( this._mouseSupport ){\n"\
"		this._$onMouseDown	= __bind(this._onMouseDown	, this);\n"\
"		this._$onMouseUp	= __bind(this._onMouseUp	, this);\n"\
"		this._$onMouseMove	= __bind(this._onMouseMove	, this);\n"\
"		this._container.addEventListener( 'mousedown'	, this._$onMouseDown	, false );\n"\
"		this._container.addEventListener( 'mouseup'	, this._$onMouseUp	, false );\n"\
"		this._container.addEventListener( 'mousemove'	, this._$onMouseMove	, false );\n"\
"	}\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype.destroy	= function()\n"\
"{\n"\
"	this._container.removeChild(this._baseEl);\n"\
"	this._container.removeChild(this._stickEl);\n"\
"\n"\
"	this._container.removeEventListener( 'touchstart'	, this._$onTouchStart	, false );\n"\
"	this._container.removeEventListener( 'touchend'		, this._$onTouchEnd	, false );\n"\
"	this._container.removeEventListener( 'touchmove'	, this._$onTouchMove	, false );\n"\
"	if( this._mouseSupport ){\n"\
"		this._container.removeEventListener( 'mouseup'		, this._$onMouseUp	, false );\n"\
"		this._container.removeEventListener( 'mousedown'	, this._$onMouseDown	, false );\n"\
"		this._container.removeEventListener( 'mousemove'	, this._$onMouseMove	, false );\n"\
"	}\n"\
"}\n"\
"\n"\
"VirtualJoystick.touchScreenAvailable	= function()\n"\
"{\n"\
"	return 'createTouch' in document ? true : false;\n"\
"}\n"\
"\n"\
";(function(destObj){\n"\
"	destObj.addEventListener	= function(event, fct){\n"\
"		if(this._events === undefined) 	this._events	= {};\n"\
"		this._events[event] = this._events[event]	|| [];\n"\
"		this._events[event].push(fct);\n"\
"		return fct;\n"\
"	};\n"\
"	destObj.removeEventListener	= function(event, fct){\n"\
"		if(this._events === undefined) 	this._events	= {};\n"\
"		if( event in this._events === false  )	return;\n"\
"		this._events[event].splice(this._events[event].indexOf(fct), 1);\n"\
"	};\n"\
"	destObj.dispatchEvent		= function(event /* , args... */){\n"\
"		if(this._events === undefined) 	this._events	= {};\n"\
"		if( this._events[event] === undefined )	return;\n"\
"		var tmpArray	= this._events[event].slice(); \n"\
"		for(var i = 0; i < tmpArray.length; i++){\n"\
"			var result	= tmpArray[i].apply(this, Array.prototype.slice.call(arguments, 1))\n"\
"			if( result !== undefined )	return result;\n"\
"		}\n"\
"		return undefined\n"\
"	};\n"\
"})(VirtualJoystick.prototype);\n"\
"\n"\
"VirtualJoystick.prototype.deltaX	= function(){ return this._stickX - this._baseX;	}\n"\
"VirtualJoystick.prototype.deltaY	= function(){ return this._stickY - this._baseY;	}\n"\
"\n"\
"VirtualJoystick.prototype.up	= function(){\n"\
"	if( this._pressed === false )	return false;\n"\
"	var deltaX	= this.deltaX();\n"\
"	var deltaY	= this.deltaY();\n"\
"	if( deltaY >= 0 )				return false;\n"\
"	if( Math.abs(deltaX) > 2*Math.abs(deltaY) )	return false;\n"\
"	return true;\n"\
"}\n"\
"VirtualJoystick.prototype.down	= function(){\n"\
"	if( this._pressed === false )	return false;\n"\
"	var deltaX	= this.deltaX();\n"\
"	var deltaY	= this.deltaY();\n"\
"	if( deltaY <= 0 )				return false;\n"\
"	if( Math.abs(deltaX) > 2*Math.abs(deltaY) )	return false;\n"\
"	return true;	\n"\
"}\n"\
"VirtualJoystick.prototype.right	= function(){\n"\
"	if( this._pressed === false )	return false;\n"\
"	var deltaX	= this.deltaX();\n"\
"	var deltaY	= this.deltaY();\n"\
"	if( deltaX <= 0 )				return false;\n"\
"	if( Math.abs(deltaY) > 2*Math.abs(deltaX) )	return false;\n"\
"	return true;	\n"\
"}\n"\
"VirtualJoystick.prototype.left	= function(){\n"\
"	if( this._pressed === false )	return false;\n"\
"	var deltaX	= this.deltaX();\n"\
"	var deltaY	= this.deltaY();\n"\
"	if( deltaX >= 0 )				return false;\n"\
"	if( Math.abs(deltaY) > 2*Math.abs(deltaX) )	return false;\n"\
"	return true;	\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._onUp	= function()\n"\
"{\n"\
"	this._pressed	= false; \n"\
"	this._stickEl.style.display	= \"none\";\n"\
"	\n"\
"	if(this._stationaryBase == false){	\n"\
"		this._baseEl.style.display	= \"none\";\n"\
"	\n"\
"		this._baseX	= this._baseY	= 0;\n"\
"		this._stickX	= this._stickY	= 0;\n"\
"	}\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._onDown	= function(x, y)\n"\
"{\n"\
"	this._pressed	= true; \n"\
"	if(this._stationaryBase == false){\n"\
"		this._baseX	= x;\n"\
"		this._baseY	= y;\n"\
"		this._baseEl.style.display	= \"\";\n"\
"		this._move(this._baseEl.style, (this._baseX - this._baseEl.width /2), (this._baseY - this._baseEl.height/2));\n"\
"	}\n"\
"	\n"\
"	this._stickX	= x;\n"\
"	this._stickY	= y;\n"\
"	\n"\
"	if(this._limitStickTravel === true){\n"\
"		var deltaX	= this.deltaX();\n"\
"		var deltaY	= this.deltaY();\n"\
"		var stickDistance = Math.sqrt( (deltaX * deltaX) + (deltaY * deltaY) );\n"\
"		if(stickDistance > this._stickRadius){\n"\
"			var stickNormalizedX = deltaX / stickDistance;\n"\
"			var stickNormalizedY = deltaY / stickDistance;\n"\
"			\n"\
"			this._stickX = stickNormalizedX * this._stickRadius + this._baseX;\n"\
"			this._stickY = stickNormalizedY * this._stickRadius + this._baseY;\n"\
"		} 	\n"\
"	}\n"\
"	\n"\
"	this._stickEl.style.display	= \"\";\n"\
"	this._move(this._stickEl.style, (this._stickX - this._stickEl.width /2), (this._stickY - this._stickEl.height/2));	\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._onMove	= function(x, y)\n"\
"{\n"\
"	if( this._pressed === true ){\n"\
"		this._stickX	= x;\n"\
"		this._stickY	= y;\n"\
"		\n"\
"		if(this._limitStickTravel === true){\n"\
"			var deltaX	= this.deltaX();\n"\
"			var deltaY	= this.deltaY();\n"\
"			var stickDistance = Math.sqrt( (deltaX * deltaX) + (deltaY * deltaY) );\n"\
"			if(stickDistance > this._stickRadius){\n"\
"				var stickNormalizedX = deltaX / stickDistance;\n"\
"				var stickNormalizedY = deltaY / stickDistance;\n"\
"			\n"\
"				this._stickX = stickNormalizedX * this._stickRadius + this._baseX;\n"\
"				this._stickY = stickNormalizedY * this._stickRadius + this._baseY;\n"\
"			} 		\n"\
"		}\n"\
"		\n"\
"        	this._move(this._stickEl.style, (this._stickX - this._stickEl.width /2), (this._stickY - this._stickEl.height/2));	\n"\
"	}	\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._onMouseUp	= function(event)\n"\
"{\n"\
"	return this._onUp();\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._onMouseDown	= function(event)\n"\
"{\n"\
"	event.preventDefault();\n"\
"	var x	= event.clientX;\n"\
"	var y	= event.clientY;\n"\
"	return this._onDown(x, y);\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._onMouseMove	= function(event)\n"\
"{\n"\
"	var x	= event.clientX;\n"\
"	var y	= event.clientY;\n"\
"	return this._onMove(x, y);\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._onTouchStart	= function(event)\n"\
"{\n"\
"	if( this._touchIdx !== null )	return;\n"\
"\n"\
"	var isValid	= this.dispatchEvent('touchStartValidation', event);\n"\
"	if( isValid === false )	return;\n"\
"	this.dispatchEvent('touchStart', event);\n"\
"\n"\
"	event.preventDefault();\n"\
"	var touch	= event.changedTouches[0];\n"\
"	this._touchIdx	= touch.identifier;\n"\
"	var x		= touch.pageX;\n"\
"	var y		= touch.pageY;\n"\
"	return this._onDown(x, y)\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._onTouchEnd	= function(event)\n"\
"{\n"\
"	if( this._touchIdx === null )	return;\n"\
"	this.dispatchEvent('touchEnd', event);\n"\
"	var touchList	= event.changedTouches;\n"\
"	for(var i = 0; i < touchList.length && touchList[i].identifier !== this._touchIdx; i++);\n"\
"	if( i === touchList.length)	return;\n"\
"	this._touchIdx	= null;\n"\
"event.preventDefault();\n"\
"\n"\
"	return this._onUp()\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._onTouchMove	= function(event)\n"\
"{\n"\
"	if( this._touchIdx === null )	return;\n"\
"	var touchList	= event.changedTouches;\n"\
"	for(var i = 0; i < touchList.length && touchList[i].identifier !== this._touchIdx; i++ );\n"\
"	if( i === touchList.length)	return;\n"\
"	var touch	= touchList[i];\n"\
"\n"\
"	event.preventDefault();\n"\
"\n"\
"	var x		= touch.pageX;\n"\
"	var y		= touch.pageY;\n"\
"	return this._onMove(x, y)\n"\
"}\n"\
"VirtualJoystick.prototype._buildJoystickBase	= function()\n"\
"{\n"\
"	var canvas	= document.createElement( 'canvas' );\n"\
"	canvas.width	= 126;\n"\
"	canvas.height	= 126;\n"\
"	\n"\
"	var ctx		= canvas.getContext('2d');\n"\
"	ctx.beginPath(); \n"\
"	ctx.strokeStyle = this._strokeStyle; \n"\
"	ctx.lineWidth	= 6; \n"\
"	ctx.arc( canvas.width/2, canvas.width/2, 40, 0, Math.PI*2, true); \n"\
"	ctx.stroke();	\n"\
"\n"\
"	ctx.beginPath(); \n"\
"	ctx.strokeStyle	= this._strokeStyle; \n"\
"	ctx.lineWidth	= 2; \n"\
"	ctx.arc( canvas.width/2, canvas.width/2, 60, 0, Math.PI*2, true); \n"\
"	ctx.stroke();\n"\
"	\n"\
"	return canvas;\n"\
"}\n"\
"VirtualJoystick.prototype._buildJoystickStick	= function()\n"\
"{\n"\
"	var canvas	= document.createElement( 'canvas' );\n"\
"	canvas.width	= 86;\n"\
"	canvas.height	= 86;\n"\
"	var ctx		= canvas.getContext('2d');\n"\
"	ctx.beginPath(); \n"\
"	ctx.strokeStyle	= this._strokeStyle; \n"\
"	ctx.lineWidth	= 6; \n"\
"	ctx.arc( canvas.width/2, canvas.width/2, 40, 0, Math.PI*2, true); \n"\
"	ctx.stroke();\n"\
"	return canvas;\n"\
"}\n"\
"VirtualJoystick.prototype._move = function(style, x, y)\n"\
"{\n"\
"	if (this._transform) {\n"\
"		if (this._has3d) {\n"\
"			style[this._transform] = 'translate3d(' + x + 'px,' + y + 'px, 0)';\n"\
"		} else {\n"\
"			style[this._transform] = 'translate(' + x + 'px,' + y + 'px)';\n"\
"		}\n"\
"	} else {\n"\
"		style.left = x + 'px';\n"\
"		style.top = y + 'px';\n"\
"	}\n"\
"}\n"\
"\n"\
"VirtualJoystick.prototype._getTransformProperty = function() \n"\
"{\n"\
"	var styles = [\n"\
"		'webkitTransform',\n"\
"		'MozTransform',\n"\
"		'msTransform',\n"\
"		'OTransform',\n"\
"		'transform'\n"\
"	];\n"\
"\n"\
"	var el = document.createElement('p');\n"\
"	var style;\n"\
"\n"\
"	for (var i = 0; i < styles.length; i++) {\n"\
"		style = styles[i];\n"\
"		if (null != el.style[style]) {\n"\
"			return style;\n"\
"		}\n"\
"	}         \n"\
"}\n"\
"  \n"\
"VirtualJoystick.prototype._check3D = function() \n"\
"{        \n"\
"	var prop = this._getTransformProperty();\n"\
"	// IE8<= doesn't have `getComputedStyle`\n"\
"	if (!prop || !window.getComputedStyle) return module.exports = false;\n"\
"\n"\
"	var map = {\n"\
"		webkitTransform: '-webkit-transform',\n"\
"		OTransform: '-o-transform',\n"\
"		msTransform: '-ms-transform',\n"\
"		MozTransform: '-moz-transform',\n"\
"		transform: 'transform'\n"\
"	};\n"\
"	var el = document.createElement('div');\n"\
"	el.style[prop] = 'translate3d(1px,1px,1px)';\n"\
"	document.body.insertBefore(el, null);\n"\
"	var val = getComputedStyle(el).getPropertyValue(map[prop]);\n"\
"	document.body.removeChild(el);\n"\
"	var exports = null != val && val.length && 'none' != val;\n"\
"	return exports;\n"\
"}\n"\
"\n"\
"			var lastPacket = \"\";\n"\
"            \n"\
"            /*\n"\
"			var connection = new WebSocket('ws://' + location.hostname + ':443/', ['arduino']);\n"\
"			connection.onopen = function() {\n"\
"				connection.send('Connect ' + new Date());\n"\
"			};\n"\
"			connection.onerror = function(error) {\n"\
"				console.log('WebSocket Error ', error);\n"\
"			};\n"\
"			connection.onmessage = function(e) {\n"\
"				console.log('Server: ', e.data);\n"\
"			};\n"\
"            */\n"\
"\n"\
"			function sendVals(speed, angle) {\n"\
"				var ret = \"\";\n"\
"				var dx = Math.round(joystick.deltaX());\n"\
"				var dy = -Math.round(joystick.deltaY());\n"\
"                var rightMSpd = 0;\n"\
"                var leftMSpd = 0;\n"\
"                \n"\
"                var rightMCmd = \"\";\n"\
"                var leftMCmd = \"\";\n"\
"				\n"\
"				if(dx == 0 && dy == 0) {\n"\
"					ret = \"stop#\";\n"\
"				}\n"\
"                else {\n"\
"					// Forward\n"\
"					if(dy >= 0) {\n"\
"						// Right\n"\
"						if(dx >= 0) {\n"\
"							leftMSpd = Math.round(speed*2.55);\n"\
"							rightMSpd = Math.round((speed - (2*angle*speed/90))*2.55);\n"\
"							leftMCmd = \"LF-\" + leftMSpd;\n"\
"							if(rightMSpd >= 0)rightMCmd = \"RF-\" + rightMSpd;\n"\
"							if(rightMSpd < 0)rightMCmd = \"RB-\" + -rightMSpd;\n"\
"						}\n"\
"						// Left\n"\
"						else {\n"\
"							rightMSpd = Math.round(speed*2.55);\n"\
"							leftMSpd = Math.round((speed - (2*angle*speed/90))*2.55);\n"\
"							rightMCmd = \"RF-\" + rightMSpd;\n"\
"							if(leftMSpd >= 0)leftMCmd = \"LF-\" + leftMSpd;\n"\
"							if(leftMSpd < 0)leftMCmd = \"LB-\" + -leftMSpd;\n"\
"						}\n"\
"					}\n"\
"					// Backward\n"\
"					if(dy < 0) {\n"\
"						// Right\n"\
"						if(dx < 0) {\n"\
"							leftMSpd = Math.round(speed*2.55);\n"\
"							rightMSpd = Math.round((speed - (2*angle*speed/90))*2.55);\n"\
"							leftMCmd = \"LB-\" + leftMSpd;\n"\
"							if(rightMSpd >= 0)rightMCmd = \"RB-\" + rightMSpd;\n"\
"							if(rightMSpd < 0)rightMCmd = \"RF-\" + -rightMSpd;\n"\
"						}\n"\
"						// Left\n"\
"						else {\n"\
"							rightMSpd = Math.round(speed*2.55);\n"\
"							leftMSpd = Math.round((speed - (2*angle*speed/90))*2.55);\n"\
"							rightMCmd = \"RB-\" + rightMSpd;\n"\
"							if(leftMSpd >= 0)leftMCmd = \"LB-\" + leftMSpd;\n"\
"							if(leftMSpd < 0)leftMCmd = \"LF-\" + -leftMSpd;\n"\
"						}\n"\
"					}\n"\
"					ret = rightMCmd + \"#\" + leftMCmd + \"#\";\n"\
"                }\n"\
"				\n"\
"				if(ret.localeCompare(lastPacket)!=0) {\n"\
"					//connection.send(ret);\n"\
"					lastPacket = ret;\n"\
"				}\n"\
"                return ret;\n"\
"			}\n"\
"			\n"\
"			console.log(\"touchscreen is\", VirtualJoystick.touchScreenAvailable() ? \"available\" : \"not available\");\n"\
"	\n"\
"			var joystick	= new VirtualJoystick({\n"\
"				container	: document.getElementById('container'),\n"\
"				mouseSupport	: true,\n"\
"				limitStickTravel: true,\n"\
"				stickRadius: 100\n"\
"			});\n"\
"			joystick.addEventListener('touchStart', function(){\n"\
"				console.log('down')\n"\
"			})\n"\
"			joystick.addEventListener('touchEnd', function(){\n"\
"				console.log('up')\n"\
"			})\n"\
"\n"\
"			setInterval(function(){\n"\
"				var outputEl	= document.getElementById('result');\n"\
"                // Evaluate speed in %\n"\
"                var speed = Math.round(Math.sqrt(joystick.deltaX()*joystick.deltaX()+joystick.deltaY()*joystick.deltaY()));\n"\
"                // Evaluate angle in every quadrant 0-90deg\n"\
"                var angle = Math.round((-(Math.atan2(joystick.deltaY(),joystick.deltaX()))*180/Math.PI));\n"\
"                if(angle < 0)angle = -angle;\n"\
"                if(angle >= 0 && angle <= 90)angle = -(angle - 90);\n"\
"                if(angle > 90 && angle <= 180)angle -= 90;\n"\
"                \n"\
"				outputEl.innerHTML	= '<b>Direction:</b> '\n"\
"					+ ' dx:'+ Math.round(joystick.deltaX())\n"\
"					+ ' dy:'+ Math.round(joystick.deltaY())\n"\
"					+ (joystick.right()	? ' Right'	 : '')\n"\
"					+ (joystick.up()	? ' Forward' : '')\n"\
"					+ (joystick.left()	? ' Left'	 : '')\n"\
"					+ (joystick.down()	? ' Backward': '')	\n"\
"                    + ' <b>Angle:</b> ' + angle + \"°\"\n"\
"                    + ' <b>Speed:</b> ' + speed + \"%\"\n"\
"                    + '<br> <b>Motors cmd:</b> ' + sendVals(speed, angle)\n"\
"				\n"\
"			}, 1/30 * 1000);\n"\
"			\n"\
"		</script>\n"\
"		\n"\
"		<div id=\"container\" style='cursor: default;'></div>\n"\
"		<div id=\"info\">\n"\
"			<div style=\"position:fixed; top:1%; color:white;\">\n"\
"				<img id='a' src='/camera' class=\"rotate180\" onload='this.style.display=\"initial\"; var b = document.getElementById(\"b\"); b.style.display=\"none\"; b.src=\"camera?\"+Date.now();'>\n"\
"				<img id='b' class=\"rotate180\" style='display: none;' src='/camera' onload='this.style.display=\"initial\"; var a = document.getElementById(\"a\"); a.style.display=\"none\"; a.src=\"camera?\"+Date.now();'>\n"\
"			</div>\n"\
"			<div style=\"position:fixed; top:1%; color:white;\"><span id=\"result\"></span></div>\n"\
"		</div> \n"\
"		\n"\
"	</body>\n"\
"</html>\n";
