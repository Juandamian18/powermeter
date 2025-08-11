(function($) {
  $.fn.menumaker = function(options) {
      var cssmenu = $(this), settings = $.extend({
          title: "Menu",  // Esta línea ya no es necesaria, se puede eliminar
          format: "dropdown",
          sticky: false
      }, options);

      return this.each(function() {
          //cssmenu.prepend('<div id="menu-button"><img src="logo.svg" alt="Logo" style="height: 30px;margin-top: 5px;margin-bottom: 5px;"></div>');
          $(this).find("#menu-button").on('click', function() {
              $(this).toggleClass('menu-opened');
              var mainmenu = $(this).next('ul');
              if (mainmenu.hasClass('open')) { 
                  mainmenu.hide().removeClass('open');
              }
              else {
                  mainmenu.show().addClass('open');
                  if (settings.format === "dropdown") {
                      mainmenu.find('ul').show();
                  }
              }
          });

          cssmenu.find('li ul').parent().addClass('has-sub');

          multiTg = function() {
              cssmenu.find(".has-sub").prepend('<span class="submenu-button"></span>');
              cssmenu.find('.submenu-button').on('click', function() {
                  $(this).toggleClass('submenu-opened');
                  if ($(this).siblings('ul').hasClass('open')) {
                      $(this).siblings('ul').removeClass('open').hide();
                  }
                  else {
                      $(this).siblings('ul').addClass('open').show();
                  }
              });
          };

          if (settings.format === 'multitoggle') multiTg();
          else cssmenu.addClass('dropdown');

          if (settings.sticky === true) cssmenu.css('position', 'fixed');

          resizeFix = function() {
              if ($( window ).width() > 768) {
                  cssmenu.find('ul').show();
              }

              if ($(window).width() <= 768) {
                  cssmenu.find('ul').hide().removeClass('open');
              }
          };
          resizeFix();
          return $(window).on('resize', resizeFix);
      });
  };
})(jQuery);

(function($){
  $(document).ready(function(){
      $("#cssmenu").menumaker({
          // Puedes quitar el título aquí o dejarlo vacío
          title: "",  // Este título ya no se utiliza
          format: "multitoggle"
      });
  });
})(jQuery);

// Canvas responsive handling
function resizeCanvases() {
  const canvases = document.querySelectorAll('canvas');
  canvases.forEach(canvas => {
    const rect = canvas.getBoundingClientRect();
    const ctx = canvas.getContext('2d');
    
    // Set canvas internal dimensions to match display size
    if (canvas.width !== rect.width || canvas.height !== rect.height) {
      canvas.width = rect.width;
      canvas.height = rect.height;
    }
  });
}

// Add resize event listener
window.addEventListener('resize', resizeCanvases);

// Initial resize call
document.addEventListener('DOMContentLoaded', function() {
  resizeCanvases();
});
