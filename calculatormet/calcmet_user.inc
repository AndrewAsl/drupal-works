<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function calcmet_set_link(){
    $output = '';
    $output .=  l(t('Калькулятор для арматуры'), '/services/calcmet/armatura').'<br>';
    $output .=  l(t('Калькулятор для двутавра'), '/services/calcmet/dvutavr').'<br>';
    $output .=  l(t('Калькулятор для квадратного проката'), '/services/calcmet/kvadrat').'<br>';
    $output .=  l(t('Калькулятор для полосового проката'), '/services/calcmet/polosa').'<br>';
    $output .=  l(t('Калькулятор для стального проката'), '/services/calcmet/steel').'<br>';
    $output .=  l(t('Калькулятор для труб'), '/services/calcmet/tube').'<br>';
    $output .=  l(t('Калькулятор для швеллеров'), '/services/calcmet/shveller').'<br>';
    $output .=  l(t('Калькулятор для шестигранников'), '/services/calcmet/shestigrannik').'<br>';
    $output .=  l(t('Калькулятор для круглого проката'), '/services/calcmet/roundprokat').'<br>';
    return $output;
}
/*
    Раздел по арматуре
 */
function calcmet_armatura_form($form, &$form_state){
    $form = array();
    $form['armatura'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone"></div>',
        //'#suffix' =>'</div>'  
    );
    
    $form['armatura']['options'] = array(
        '#title' => t('Диаметр стержня'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetarmatura'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите диаметр арматуры'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'armatura_change_info',
        ),*/
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['armatura']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'armatura_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['armatura']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       '#suffix' =>'</div>'
    );
    $form['armatura']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/armatura.jpg"></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['armatura']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="armatura-info"><strong>Площадь поперечного сечения, см<sup>2</sup>:</strong> <span id="csa">0.283</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.222</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 5781-82 "Сталь горячекатаная для армирования железобетонных конструкций. '
        . 'Технические условия" утвержден постановлением Госстандарта Республики Беларусь '
        . 'от 17.12.1992 № 3, с учетом изменения № 5',
        '#prefix' => '<div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div>',        
    );
    
    $form['armatura']['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-9"> Спецификация</div>'
        .'<div class="col-md-3"><span class="glyphicon glyphicon-print"></span></div>'
        .'<div><table id="spec" class="table"><tbody>'
        . '<tr>'
        . '<th>№ п/п</th>'
        . '<th>Наименование</th>'
        . '<th>Длина, м</th>'
        . '<th>Масса, кг</th>'
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetdata.js',
    );
    return $form;
}
/*
 * Конец формы для арматуры
 */
/*
    Раздел по двутавру
 */
function calcmet_dvutavr_form($form, &$form_state){
    $form = array();
    $form['dvutavr'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone"></div>',
        //'#suffix' =>'</div>'  
    );
    
    $form['dvutavr']['options'] = array(
        '#title' => t('Номер двутавра'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetdvutavr'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип двутавра'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'dvutavr_change_info',
        ),*/
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['dvutavr']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'dvutavr_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['dvutavr']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['dvutavr']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м2'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['dvutavr']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/dvutavr.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['dvutavr']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="dvutavr-info">'
        . '<strong>Высота (h), мм:</strong> <span id="height">100</span><br>'
        . '<strong>Ширина (b), мм:</strong> <span id="width">55</span><br>'
        . '<strong>Толщина (s), мм:</strong> <span id="thickness">4.5</span><br>'
        . '<strong>Толщина полки (t), мм</strong> <span id="polkathickness">7.2</span><br>'
        . '<strong>Площадь сечения, см2</strong> <span id="csa">12</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">9.46</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8239-89 "Двутавры стальные горячекатаные.' 
        . 'Сортамент" утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 г. № 3',
        '#prefix' => '<div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div>',        
    );
    
    $form['dvutavr']['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-9"> Спецификация</div>'
        .'<div class="col-md-3"><span class="glyphicon glyphicon-print"></span></div>'
        .'<div><table id="spec" class="table"><tbody>'
        . '<tr>'
        . '<th>№ п/п</th>'
        . '<th>Наименование</th>'
        . '<th>Длина, м</th>'
        . '<th>Масса, кг</th>'
        . '<th>Площадь окраски, кг</th>'
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetdvutavr.js',
    );
    return $form;
}
/*
 * Конец формы для двутавра
 */
/*
    Раздел по квадрату
 */
function calcmet_kvadrat_form($form, &$form_state){
    $form = array();
    $form['armatura'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone"></div>',
        //'#suffix' =>'</div>'  
    );
    
    $form['armatura']['options'] = array(
        '#title' => t('Диаметр стержня'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetarmatura'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите диаметр арматуры'),
        '#ajax' => array(
            'wrapper' => '',
            'callback' => 'armatura_change_info',
        ),
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['armatura']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_integer_positive'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'armatura_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['armatura']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       '#suffix' =>'</div>'
    );
    $form['armatura']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/kvadrat.jpg" height=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['armatura']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="armatura-info"><strong>Площадь поперечного сечения, см<sup>2</sup>:</strong> <span id="csa">0.283</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.222</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 5781-82 "Сталь горячекатаная для армирования железобетонных конструкций. '
        . 'Технические условия" утвержден постановлением Госстандарта Республики Беларусь '
        . 'от 17.12.1992 № 3, с учетом изменения № 5',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>',        
    );
    $form['armatura']['spec'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4"> id="btnspec"',
       '#suffix' =>'</div>',        
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetdata.js',
    );
    return $form;
}
/*
 * Конец формы для квадрата
 */
/*
    Раздел по полосе
 */

/*
 * Конец формы для полосы
 */
/*
    Раздел по стали
 */

/*
 * Конец формы для стали
 */
/*
    Раздел по трубам
 */

/*
 * Конец формы для труб
 */
/*
    Раздел по швеллерам
 */

/*
 * Конец формы для швеллеров
 */
/*
    Раздел по шестигранникам
 */

/*
 * Конец формы для шестигранников
 */
/*
    Раздел по круглому прокату (пруткам)
 */

/*
 * Конец формы для круглого проката
 */

function armatura_change_info(){
    $select = $_POST['armaturaselect'];
    //dsm($select);
    $infos = db_select('calcmetarmatura', 'a')
            ->fields('a', array('csa', 'massonem'))
            ->condition('a.adid', $select)
            ->execute()
            ->fetchAll();
    //dsm($infos);
    $csa = $infos[0]->csa;
    $massonem = $infos[0]->massonem;
    drupal_json_output(array('csa' => $csa, 'massonem'=>$massonem));
    drupal_exit();
}
function dvutavr_change_info(){
    $select = $_POST['dvutavrselect'];
    //dsm($select);
    $infos = db_select('calcmetdvutavr', 'd')
            ->fields('d', array('dvutavrheight', 'dvutavrwidth', 'dvutavrthickness', 'dvutavrthicknesspolka', 'csa', 'massonem', 'drawonemetr'))
            ->condition('d.dvdid', $select)
            ->execute()
            ->fetchAll();
    $dvutavrheight = $infos[0]->dvutavrheight;
    $dvutavrwidth = $infos[0]->dvutavrwidth;
    $dvutavrthickness = $infos[0]->dvutavrthickness;
    $dvutavrthicknesspolka = $infos[0]->dvutavrthicknesspolka;
    $csa = $infos[0]->csa;
    $massonem = $infos[0]->massonem;
    $drawonemetr = $infos[0]->drawonemetr;
    drupal_json_output(array(
                        'dvutavrheight' => $dvutavrheight,
                        'dvutavrwidth' => $dvutavrwidth,
                        'dvutavrthickness' => $dvutavrthickness,
                        'dvutavrthicknesspolka' => $dvutavrthicknesspolka,
                        'csa' => $csa, 
                        'massonem'=>$massonem,
                        'drawonemetr'=>$drawonemetr,
                        
        ));
    drupal_exit();
}



function _get_undercategory_options($cat){
    $entries = db_select('calcmetundercat', 'uc')
            -> fields('uc')
            -> condition ('uc.ccid', $cat)
            -> execute()
            -> fetchAll();
    //dsm($entries);
    foreach ($entries as $entry) {
      $options[$entry->cucid] = $entry->title;
    }
    if (isset($options)) {
        return $options;
    }
    else {
        return array('В данной категории подразделы отсуствуют');
    }
}

function _tube_change_calculator_type($form, &$form_state){
  //$form_state['rebuild'] = TRUE; 
   //$values = $form_state['values'];
  // Overwrite the student list fields with new options value.
  //$form['calculatedzone']['calculator']['tubename'] = array(
   // '#type' => 'checkboxes',
    //'#options' => _get_tube_name_for_options($values['tubeundercategory']), // Api will return the class students list as array.
  //);
  //$form['calculatedzone']['calculator']['tubename'] = form_process_checkboxes($form['calculatedzone']['calculator']['tubename']); // Process the checkboxes fields.
  //return $form['calculatedzone']['calculator']; // return full students field container.
  //ajax_deliver($form['calculatedzone']['calculator']);  
    $commands[] = ajax_command_alert('This alert message');
    $page = array('#type' => 'ajax', '#commands' => $commands);
    ajax_deliver($page);
    //return array('#type' => 'ajax', '#commands' => $commands);
}


function _get_tube_name_for_options ($case){
    //dsm($case);
    switch ($case) {
        case 5:
            $basename = 'calcmettubessteelwithoutseam';
            break;
        case 6:
            $basename = 'calcmettubestellsvarnpryamoshovn';
            break;
        default:
            $basename = 'calcmettubessteelwithoutseam';
            break;
    }
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    //dsm($entries);
    foreach ($entries as $entry) {
      if ($basename == 'calcmettubestellsvarnpryamoshovn'){  
        $options[$entry->tsshdid] = $entry->tsshname;
      }
    }
    //if (isset($options)) {
        return $options;
    //}
}

function calcmet_get_options ($basename){
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetarmatura':
                $options[$entry->adid] = $entry->diametr;
                break;
            case 'calcmetdvutavr':
                $options[$entry->dvdid] = $entry->dvutavrname;
                break;

            default:
                break;
        }
    }
    return $options;
}