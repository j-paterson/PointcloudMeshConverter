/* borrowing slideshow css from https://themarklee.com/2013/12/26/simple-diy-responsive-slideshow-made-html5-css3-javascript/
  */

$(document).ready(function(){
 
	var counter = 0,
	$items = $('.diy-slideshow figure'),
	numItems = $items.length;
	 
	var showCurrent = function(){
	var itemToShow = Math.abs(counter%numItems);
	$items.removeClass('show');
	$items.eq(itemToShow).addClass('show');
	};
	 
	$('.next').on('click', function(){
	counter++;
	showCurrent();
	});
	 
	$('.prev').on('click', function(){
	counter--;
	showCurrent();
	});
 
});